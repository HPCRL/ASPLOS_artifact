/**
   dst ( n, oc, oh, ow) = bias(oc) + \sum_ic \sum_kh \sum_kw src(n, ic, oh*SH+kh-ph0, ow*SW+kw-pw0) * weights(oc, ic, kh, kw)   
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include <cmath>
#include <numeric>
#include <sstream>
#include <vector>
#include <assert.h>
#include "dnnl_debug.h"
#include "example_utils.hpp"
#include "omp.h"
using namespace dnnl;
using namespace std;
#define TOTITER 1
memory::dim product(const memory::dims &dims) {
    return std::accumulate(dims.begin(), dims.end(), (memory::dim)1,
            std::multiplies<memory::dim>());
}
int compare(float*C1, vector<float>&C2, int size) {
  cout << "comparing" << endl;
  for (int i = 0; i < size; i++) {
    if (C1[i] != C2[i]) {
      cout << "data at " << i << " C1=" << C1[i] << ", C2=" << C2[i] << endl;
      return -1;
    }
  }
  cout << "fin compare\n";
  return 0;
}
 void origin_conv(vector<float>& In, vector<float> &Ker, vector<float> &Out, int Nb, int Nt, int Nx,
                 int Ny, int Ns, int Nw, int Nh, int StrideX, int StrideY) {
    int LOF=1;
    int LC=1;
    int LKF=1;
        
#pragma omp parallel for collapse(5)
  for (int b = 0; b < Nb; b++) {
    for (int t = 0; t < Nt; t++) {
      for (int x = 0; x < Nx; x++) {
        for (int y = 0; y < Ny; y++) {
            for (int w = 0; w < Nw; w++) {
                for (int h = 0; h < Nh; h++) {
                    for (int s = 0; s < Ns; s++) {    

                /* Out[b * Nt * Nx * Ny + t * Nx * Ny + x * Ny + y] += */
                /*     In[b * Ns * (Nx + Nw - 1) * (Ny + Nh - 1) + */
                /*        s * (Nx + Nw - 1) * (Ny + Nh - 1)  + */
                /*        (x + w) * (Ny + Nh - 1) + (y + h)] * */
                /*     Ker[t * Ns * Nw * Nh + s * Nw * Nh + w * Nh + h]; */

                  int kt1 = t /LKF;
                  int kt2 = t %LKF;
                  int ot1 = t /LOF;
                  int ot2 = t %LOF;
                  
                  int s1 = s / LC;
                  int s2 = s%LC;
                  int Ooffset = b* Nt * Nx * Ny + ot1 * Nx * Ny*LOF +  x*Ny*LOF + y*LOF + ot2;
                  int Ioffset = b * Ns * (StrideX*Nx + Nw - 1) * (StrideY*Ny + Nh - 1) +
                      s1 * (StrideX*Nx + Nw - 1) * (StrideY*Ny + Nh - 1) * LC +
                      (StrideX*x + w) * (StrideY*Ny + Nh - 1)*LC + (StrideY*y + h) * LC + s2;
                  int Koffset = kt1 * Ns * Nw * Nh * LKF + s * Nw * Nh*LKF + w * Nh*LKF + h*LKF + kt2;
                  Out[Ooffset] += In[Ioffset]* Ker[Koffset];



                  // if(Ooffset == 896){
                  //     cout<<"Inoff="<<Ioffset<<", Koff="<<Koffset<<endl;
                  // }
              }
            }
          }
        }
      }
    }
  }
}

void test_conv(engine::kind engine_kind, long long nb, long long nw, long long ns, long long nx, long long ny, long long nf, long long nc, int sx, int sy){
    using tag = memory::format_tag;
    engine eng(engine_kind, 0);
    stream engine_stream(eng);
    stream s(eng);

    std::vector<primitive> net;
    std::vector<std::unordered_map<int, memory>> net_args;
//    dst(b, f, x, y) = in(b, c, x+w, y+s) * ker(f,c,w,s);
    
    //size:
//    b = 256, x=y=224,112,56,28,14,7  (f=64 c=3), (f=64,c=64) (128,64),(128,128), (256,128),(256,256), w=s=3 or 7

    const int B = nb, W = nw, S = ns, X = nx, Y = ny, F = nf, C =nc;
//        const int B = 1, W = 3, S = 3, X = 224, Y = 224, F = 64, C =3;
    const long long stride_ob = F*X*Y;
    const long long stride_of = X*Y;
    const long long stride_ox = Y;
    const long long stride_oy = 1;

    const long long stride_ib = C*(sx*X+W-1)*(sy*Y+S-1);
    const long long stride_ic = (sx*X+W-1)*(sy*Y+S-1);
    const long long stride_ix = (sy*Y+S-1);
    const long long stride_iy = 1;

    const long long stride_kf = C*W*S;
    const long long stride_kc = W*S;
    const long long stride_kw = S;
    const long long stride_ks = 1;

    auto o_offset = [=](long long b, long long f, long long x, long long y){
                        return b*stride_ob + f*stride_of + x*stride_ox + y*stride_oy;
                    };

    auto i_offset = [=](long long b, long long c, long long x, long long y){
                        return b*stride_ib + c*stride_ic + x*stride_ix + y*stride_iy;
                    };

    auto k_offset = [=](long long f, long long c, long long w, long long s){
                        return f*stride_kf + c*stride_kc + w*stride_kw + s*stride_ks;
                    };



    std::vector<float> batch_out [TOTITER];
    std::vector<float> batch_ker [TOTITER];
    std::vector<float> batch_inp [TOTITER];
    auto user_output_mem = memory({ {B, F, X, Y}, memory::data_type::f32, tag::nchw }, eng);
    

        std::vector<float> output(B*F*X*Y);
        std::vector<float> input(B*C*(sx*X+W-1)*(sy*Y+S-1));
        std::vector<float> kernel(F*C*W*S);


//    std::vector<float> conv_bias(F);
        memory::dims conv_strides = {sx,sy};
        memory::dims conv_padding = {0,0};
//    memory::dims conv_bias_tz = {F};    
    
        std::cout<<"ck1"<<std::endl;
        for(int b = 0; b<B; b++)
        for(int c = 0; c<C; c++)
        for(int x = 0; x<sx*X+W-1; x++)
        for(int y = 0; y<sy*Y+S-1; y++)
        {
            int ioff = i_offset(b,c,x,y);
            input[ioff] = rand()%10;//-std::cos(ioff / 10.0f);

        }


        for(int f = 0; f<F; f++)
        for(int w = 0; w<W; w++)
        for(int c = 0; c<C; c++)
        for(int s = 0; s<S; s++)
        {
            int koff = k_offset(f,c,w,s);
            kernel[koff] = rand()%10;//-std::cos(koff/10.0f);

        }


        batch_out[0] = output;
        batch_ker[0] = kernel;
        batch_inp[0] = input;


        auto input_md = memory::desc(
            {B, C, (sx*X+W-1), (sy*Y+S-1)},
            memory::data_type::f32,
            tag::any//{stride_ib, stride_ic, stride_ix, stride_iy}
            );
    
        auto output_md = memory::desc(
            {B, F, X, Y},
            memory::data_type::f32,
            tag::any//{stride_ob, stride_of, stride_ox, stride_oy}
            );

        auto kernel_md = memory::desc(
            {F, C, W, S},
            memory::data_type::f32,
            tag::any//{stride_kf, stride_kc, stride_kw, stride_ks}
            );

//    auto bias_md = memory::desc({conv_bias_tz}, memory::data_type::f32, tag::any);
        // auto input_mem = memory(input_md, eng);
        // auto output_mem = memory(output_md, eng);
        // auto kernel_mem = memory(kernel_md, eng);

        auto user_input_mem = memory({ {B, C, sx*X+W-1, sy*Y+S-1}, memory::data_type::f32, tag::nchw }, eng);
        auto user_kernel_mem = memory({ {F, C, W, S}, memory::data_type::f32, tag::oihw }, eng);
//    auto user_bias_mem = memory({{conv_bias_tz }, memory::data_type::f32, tag::x}, eng);
//    cout<<"start omp wtime\n";
//    double start = omp_get_wtime();    
        write_to_dnnl_memory(input.data(), user_input_mem);
        write_to_dnnl_memory(kernel.data(), user_kernel_mem);
//    write_to_dnnl_memory(conv_bias.data(), user_bias_mem);    
        std::cout<<"conv desc create\n";

//    auto conv_desc =
//        convolution_forward::desc(prop_kind::forward_inference,
//                                  algorithm::convolution_direct, input_md, kernel_md, bias_md,
//                                  output_md, conv_strides, conv_padding, conv_padding);
        auto conv_desc = convolution_forward::desc(prop_kind::forward_inference,
                                                   algorithm::convolution_direct, input_md, kernel_md,
                                                   output_md, conv_strides, conv_padding,
                                                   conv_padding);
        
        std::cout<<"conv prim desc create\n";
        auto conv_prim_desc = convolution_forward::primitive_desc(conv_desc, eng);

        auto conv_input_mem = user_input_mem;
        if( conv_prim_desc.src_desc() != user_input_mem.get_desc()){
            conv_input_mem = memory(conv_prim_desc.src_desc(), eng );            
            net.push_back(reorder(user_input_mem, conv_input_mem));
            net_args.push_back(
                { {DNNL_ARG_FROM, user_input_mem}, {DNNL_ARG_TO, conv_input_mem} }
                );
        }

        auto conv_kernel_mem = user_kernel_mem;
        // never reorder kernel, let oneDNN pick whatever kernel it likes.
        if(conv_prim_desc.weights_desc() != user_kernel_mem.get_desc()){
            std::cout<<"reorder ker_input to "<<endl;
            conv_kernel_mem = memory(conv_prim_desc.weights_desc(), eng);
            net.push_back(reorder(user_kernel_mem, conv_kernel_mem));
            net_args.push_back(
                {{DNNL_ARG_FROM, user_kernel_mem}, {DNNL_ARG_TO, conv_kernel_mem}}
                );
        }

        auto conv_output_mem = memory(conv_prim_desc.dst_desc(), eng);

        net.push_back(convolution_forward(conv_prim_desc));
        net_args.push_back(
            { {DNNL_ARG_SRC, conv_input_mem},
                {DNNL_ARG_WEIGHTS, conv_kernel_mem},
//          {DNNL_ARG_WEIGHTS, user_bias_mem},
                {DNNL_ARG_DST, conv_output_mem}
            });

        if( conv_prim_desc.dst_desc() != user_output_mem.get_desc()){
            printf("reorder out\n");
            net.push_back(reorder(conv_output_mem, user_output_mem));
            printf("reorder out\n");
            net_args.push_back(
                { {DNNL_ARG_FROM, conv_output_mem}, {DNNL_ARG_TO, user_output_mem} }
                );
        }

    
    assert(net.size() == net_args.size() && "something is missing, net size != net arg size\n");
//    std::cout<<"start!\n";
    vector<double> gflop_array;
    double flop_cnt = 2.0*B*W*S*X*Y*C*F*TOTITER;
    // int totiter = TOTITER;

    //     float ressss;
    // float tttmp[8];
    // int flushsz=100000000;
//    for(int iter = 0; iter< totiter; iter++ ){
        // float *dirty = (float *)malloc(flushsz * sizeof(float));
        // #pragma omp parallel for
        //     for (int dirt = 0; dirt < flushsz; dirt++){
        //         dirty[dirt] += dirt%100;
        //         tttmp[dirt%8] += dirty[dirt];
        //     }
        //     for(int ii =0; ii<8;ii++){ressss+= tttmp[ii];}
        //     cout<<"flush"<<ressss<<endl;            
//            cout<<"start\n";

    ////////////////////////////////////////////////////
     std::vector<float> comp_output = batch_out[0]; //
    ////////////////////////////////////////////////////
    float ressss;
    float tttmp[18];
    int flushsz=100000000;

    


    int totiter = 50;
    vector<double> gflops;
    for (int i = 0; i< totiter; i++){
        float *dirty = (float *)malloc(flushsz * sizeof(float));
#pragma omp parallel for
        for (int dirt = 0; dirt < flushsz; dirt++){
            dirty[dirt] += dirt%100;
            tttmp[dirt%18] += dirty[dirt];
        }
        for(int ii =0; ii<18;ii++){ressss+= tttmp[ii];}
        cout<<"flush"<<ressss<<endl;            
        cout<<"start\n";

        double start2 = omp_get_wtime();
        for(size_t i = 0; i < net.size(); i++){
            net.at(i).
                execute(
                    s, net_args.at(i));
        }
        s.wait();
        double end = omp_get_wtime();
        free(dirty);
        double avg_gflop=(1.0*flop_cnt/(end-start2)/1000.0/1000.0/1000.0);
        gflops.push_back(avg_gflop);
    }
    double average = 0;
    cout<<"print flops"<<endl;
    for (auto i : gflops){
        cout<<i<<endl;
        average += i;
    }
    cout<<"avg flops,"<<average/totiter<<endl;
    
//        cout<<"end\n";
//        free(dirty);
//    origin_conv(batch_inp[0], batch_ker[0], comp_output, B, F, X, Y, C, W, S, sx, sy) ;       //
//    compare((float*)user_output_mem.get_data_handle(), comp_output, B*F*X*Y);                                              //
    

//    std::cout<<"exe time flop = "<<flop_cnt/(end-start2)/1000.0/1000.0/1000.0<<endl;
//    std::cout<<"before wait!\n";
        //cout<<"avg gflop"<<avg_gflop<<endl;
    
//    std::cout<<"fin\n";
//    std::cout<<"all time = "<<end-start<<endl;
//    std::cout<<"exe time = "<<end-start2<<endl;
//    std::cout<<"all time flop = "<<flop_cnt/(end-start)/1000.0/1000.0/1000.0<<endl;


}


int main(int argc, char**argv){
    try{
	    int nb = atoi(argv[1]);
	    int nf = atoi(argv[2]);
	    int nx = atoi(argv[3]);
	    int ny = atoi(argv[4]);
	    int nc = atoi(argv[5]);
	    int nw = atoi(argv[6]);
	    int nh = atoi(argv[7]);
            int sx = atoi(argv[8]);
            int sy = atoi(argv[9]);
	    std::cout << "nb, " << nb << ", nf, " << nf << " nx " << nx << " ny " << ny << " nc "<< nc << " nw " << nw << " nh " << nh << "\n";
        engine:: kind engine_kind = parse_engine_kind(argc, argv);
	std::cout<<"hello\n";
	test_conv(engine_kind, nb, nw, nh, nx, ny, nf, nc, sx, sy);
        std::cout<<" conv pass\n";        
    }catch(dnnl::error &e){
        std::cerr << "DNNL error: " << e.what() << std::endl
                  << "Error status: " << dnnl_status2str(e.status) << std::endl;
        return 1;
    } catch (std::string &e) {
        std::cerr << "Error in the example: " << e << std::endl;
        return 2;
    }

    return 0;    
    
}

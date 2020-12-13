#pragma once
#include <iostream>
#include <assert.h>
using std::cout;
using std::endl;

void ukr_ref(float*A, float*B, float*C,
             int numA, int numB, int ctile,
             int ifcstride, int kfstride, 
             int winx, int winy, int Nx, int Ny, int Nc, int Nf){
    for(int ci = 0; ci < ctile; ci++){
        for (int wi = 0; wi < winx; wi++){
            for (int hi =0; hi < winy; hi++){
                for(int xy =0 ; xy < numA; xy++){
                    for(int fi =0; fi < numB; fi++){
                        int offstride = ifcstride;
                        int offsetA = // c1 x y c2
                            (ci/ifcstride) * (Nx+winx-1) * (Ny+winy-1) * ifcstride
                            + (xy + wi*((Ny+winy-1)) + hi) * ifcstride + (ci%ifcstride);
                        int offsetB = // f c1 x y c2
                            (fi/kfstride) * (Nc*winx*winy*kfstride) +
                            (ci * winx*winy*kfstride) +
                            (hi + wi*winy) * kfstride + (fi%kfstride);
                        int offsetC = // c1 x y c2
                            (fi/offstride) * Nx * Ny * offstride
                            + (xy) * offstride + (fi%offstride);
                        if(offsetC==-1){
                            cout<<"Coff="<<offsetC<<", Aoff="<<offsetA<<", Boff="<<offsetB<<",";
                            printf(" c=%d, w=%d, h=%d, xy=%d, f=%d\n", ci, wi,hi, xy, fi);
                        }
                        C[offsetC] += A[offsetA] * B[offsetB];
                    }//fi
                }//sy
            }//hi
        }//wi
    }//ci
}


void ukr_full(float* A, float*B, float*C, long long ctile, long long * Astrides){
    const int rxy =3;
    const int rf = 24;

    const int rw = uNw;
    const int rh = uNh;
    assert(ctile%LC==0);
    int tc1= ctile/LC;
    int tc2= LC;


    int tkf2 = LKF;
    int tof2 = LOF;

    bool flag = false;
    
    for(int c1_1 = 0; c1_1 < tc1; c1_1 ++){
        for (int w1 =0 ; w1 < rw; w1++){
            for(int h1 = 0; h1 < rh; h1++){
                for(int c1_2 = 0; c1_2 < tc2; c1_2 ++){
                    for(int img = 0; img< rxy ; img++){
                        int xy1 = Astrides[img];
                        for(int f1 = 0; f1 < rf; f1++){
                            int Coffset = img*tof2 + f1%tof2 + f1/tof2 * uNy*uNx*tof2;
                            int Aoffset = xy1 + h1*tc2 + w1*(uNy+uNh-1)*tc2 + c1_2 + c1_1* (uNx+uNw-1)*(uNy+uNh-1)*tc2;
                            int Boffset = (c1_1*tc2+c1_2)* uNh*uNw*tkf2  + w1*uNh*tkf2  + h1*tkf2  + f1%tkf2 + (f1/tkf2)*uNh*uNw*tkf2*uNc ;


                            // if(Coffset + coff == 896){
                            //     cout<< "Aof="<<aoff<<",bof="<<boff<<"   ";
                            //     cout<< "Aoffset="<<Aoffset<<",Boffset="<<Boffset<<"   ";
                            //     cout<< "xy1="<<xy1<< "img="<<img<<" ,f1="<<f1<<" ,c1_1="<<c1_1<<" ,c1_2="<<c1_2<<" ,w1="<<w1<<" ,h1="<<h1<<endl;
                            //     flag = true;
                            // }
                            C[Coffset] += 
                                A[Aoffset] *
                                B[ Boffset];
                        }
                    }
                }
            }
        }
    }
//    if(flag)exit(1);
}


void ukr_part_img(float* A, float*B, float*C, long long ctile, long long * Astrides){

    const int rxy = EdgeXY;
    const int rf = 16;

    const int rw = uNw;
    const int rh = uNh;

    assert(ctile%LC==0);
    
    int tc1= ctile/LC;
    int tc2= LC;

    int tkf2 = LKF;
    int tof2 = LOF;
//    int tf2 = LF;
    
    for(int c1_1 = 0; c1_1 < tc1; c1_1 ++){
        for (int w1 =0 ; w1 < rw; w1++){
            for(int h1 = 0; h1 < rh; h1++){
                for(int c1_2 = 0; c1_2 < tc2; c1_2 ++){
                    for(int img = 0; img< rxy ; img++){
                        int xy1 = Astrides[img];
                        for(int f1 = 0; f1 < rf; f1++){
                            // int Coffset = img*16 + f1;
                            // int Aoffset = xy1 + h1*16 + w1*114*16 + c1_2 + c1_1* 114*114*16;
                            // int Boffset = (c1_1*16+c1_2)* 3*3*16  + w1*3*16  + h1*16  + f1;
//                            int Coffset = img*tf2 + f1;

//                            int Coffset = img*tf2 + f1%tf2 + f1/tf2 * uNy*uNx*tf2;
                            int Coffset = img*tof2 + f1%tof2 + f1/tof2 * uNy*uNx*tof2;
                            int Aoffset = xy1 + h1*tc2 + w1*(uNy+uNh-1)*tc2 + c1_2 + c1_1* (uNx+uNw-1)*(uNy+uNh-1)*tc2;
//                            int Boffset = (c1_1*tc2+c1_2)* uNh*uNw*tf2  + w1*uNh*tf2  + h1*tf2  + f1;
                            //       int Boffset = (c1_1*tc2+c1_2)* uNh*uNw*tf2  + w1*uNh*tf2  + h1*tf2  + f1%tf2 + (f1/tf2)*uNh*uNw*tf2*uNc ;
                            int Boffset = (c1_1*tc2+c1_2)* uNh*uNw*tkf2  + w1*uNh*tkf2  + h1*tkf2  + f1%tkf2 + (f1/tkf2)*uNh*uNw*tkf2*uNc ;
                            C[Coffset] += 
                                A[Aoffset] *
                                B[ Boffset];

/*                             if(Coffset + coff == 200640){ */
/* //                            if(coff == 200640 && f1 ==0){ */
/*                                 cout<< "coffset="<< Coffset + coff<< "xy1="<<xy1<<",img="<<img<<endl; */
/*                                 cout<<"gen offset = "<<aoff + Aoffset<<", "<<boff + Boffset<<endl; */
/*                                 printf("xy1 %d, h1 %d, w1 %d, c1_1 %d, c1_2 %d, f1 %d\n", xy1, h1, w1, c1_1, c1_2, f1); */
//                            }
                        }
                    }
                }
            }
        }
    }
}
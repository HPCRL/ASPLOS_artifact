import logging
import sys
import os
import numpy as np

import tvm
from tvm import autotvm
from tvm.autotvm.tuner import XGBTuner, GATuner, RandomTuner, GridSearchTuner
import tvm.contrib.graph_runtime as runtime
from tvm.autotvm.task.topi_integration import deserialize_args
from collections import namedtuple
from topi.testing import conv2d_nchw_python

num_threads = 1
os.environ["TVM_NUM_THREADS"] = str(num_threads)

tuning_option = {
    'tuner': 'xgb',
    'early_stopping': None,

    'measure_option': autotvm.measure_option(
        builder=autotvm.LocalBuilder(timeout=100),
        runner=autotvm.LocalRunner(number=5, timeout=100),
    ),
}


def tune_kernels(N, H, W, CO, CI, KH, KW, strides, padding, dilation, trials, log_filename, so_file,
                 measure_option,
                 tuner,
                 early_stopping,
                 ):
    # N, H, W, CO, CI, KH, KW, strides, padding, dilation = 1, 7, 7, 512, 512, 3, 3, (1, 1), (1, 1), (1,1)
    data = ('TENSOR', (N, CI, H, W), 'float32')
    kernel = ('TENSOR', (CO, CI, KH, KW), 'float32')

    # data = deserialize_args( ('TENSOR', tvm.placeholder((N, CI, H, W), dtype='float32', name='data')) )
    # kernel = deserialize_args(('TENSOR',tvm.placeholder((CO, CI, KH, KW), dtype='float32', name='kernel')) )
    origin_layout = 'NCHW'
    func_create = 'topi_x86_conv2d_NCHW_test'
    task = autotvm.task.create(func_create,
                               args=(data, kernel, strides, padding, 1, origin_layout, 'float32'),
                               target='llvm -mcpu=core-avx2', template_key='direct')
    # task.workload = ['float32', 'float32', H, W, CI, 1, CO, KH, KW, 1, 1, 1, 1]
    print(task.config_space)
    trials = min(trials, len(task.config_space))

    # During tuning we will also try many invalid configs, so you are expected to
    # see many error reports. As long as you can see non-zero GFLOPS, it is okay.
    tuner = autotvm.tuner.XGBTuner(task, loss_type='rank')
    # tuner.tune(n_trial=trials,
    #           measure_option=measure_option,
    #           callbacks=[
    #               autotvm.callback.progress_bar(trials),
    #               autotvm.callback.log_to_file(log_filename)])

    dispatch_context = autotvm.apply_history_best(log_filename)
    best_config = dispatch_context.query(task.target, task.workload)
    print("\nBest config:")
    print(best_config)
    with autotvm.apply_history_best(log_filename):
        with tvm.target.create("llvm -mcpu=core-avx2"):
            s, arg_bufs = task.func(data, kernel, strides, padding, 1, origin_layout, 'float32', best_config)
            func = tvm.build(s, arg_bufs, "llvm -mcpu=core-avx2", name="fconv")
            print("arg_bufs 0", arg_bufs[0])
            print("arg_bufs 1", arg_bufs[1])
            print("arg_bufs 2", arg_bufs[2])
            # print(func.get_source())
            ''' 
            dump = "%s.ll" % log_filename
            f = open(dump, "a")
            f.write(func.get_source())
            f.close()
	    '''
    path_dso = "...your so file path" % so_file
    m = tvm.module.load(path_dso)
    fconv = m['fconv']
    iteration = 50
    a_np = np.random.uniform(size=(N, CI, H, W)).astype(np.float32)
    w_np = np.random.uniform(size=(CO, CI, KH, KW)).astype(np.float32)
    c_np = conv2d_nchw_python(a_np, w_np, strides, padding)
    a_tvm = tvm.nd.array(a_np)
    w_tvm = tvm.nd.array(w_np)
    c_tvm = tvm.nd.empty(c_np.shape)


    print("\n============= Conti  ====================\n")
    for x in range(0, iteration):
        fconv(a_tvm, w_tvm, c_tvm)
        tvm.testing.assert_allclose(c_np, c_tvm.asnumpy(), rtol=1e-2)
    print("\n============= Conti DONE====================\n")

    outH = arg_bufs[2].shape[2];
    outW = arg_bufs[2].shape[3];
    ctx = tvm.cpu()
    evaluator = func.time_evaluator(func.entry_name, ctx, number=500)
    time = evaluator(a_tvm, w_tvm, c_tvm).mean
    total_flop = 2 * N * outH * outW * CO * CI * KH * KW
    print('\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^')
    print('total_flop : ', total_flop)
    print('Time cost of this operator: %f' % time)
    print('GLFOPs : %f', (total_flop/ time / 1000/1000/1000) )
    print('^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n')


def tune_and_evaluate(tuning_opt):
    print("strat tuning...")

    assert (len(sys.argv) == 13)
    log_file = sys.argv[11]
    so_file = sys.argv[12]
    trials = int(sys.argv[10])

    N = int(sys.argv[1])
    H = int(sys.argv[2])
    W = int(sys.argv[3])
    CO = int(sys.argv[4])
    CI = int(sys.argv[5])
    KH = int(sys.argv[6])
    KW = int(sys.argv[7])
    strides = int(sys.argv[8])
    padding = int(sys.argv[9])

    dilation = 1;
    # print("N, H, W, CO, CI, KH, KW, strides, padding \n" , N, H, W, CO, CI, KH, KW, strides, padding)
    tune_kernels(N, H, W, CO, CI, KH, KW, strides, padding, dilation, trials, log_file, so_file,**tuning_option)


tune_and_evaluate(tuning_option)


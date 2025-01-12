#include <stdexcept>
#include <wamr/native.h>
#include <wasm/openmp.h>
#include <wasm_export.h>

namespace wasm {
static void __kmpc_barrier_wrapper(wasm_exec_env_t execEnv,
                                   int32_t loc,
                                   int32_t globalTid)
{
    wasm::doOpenMPBarrier(loc, globalTid);
}

static void __kmpc_end_master_wrapper(wasm_exec_env_t execEnv,
                                      int32_t loc,
                                      int32_t globalTid)
{
    wasm::doOpenMPEndMaster(loc, globalTid);
}

static void __kmpc_for_static_fini_wrapper(wasm_exec_env_t execEnv,
                                           int32_t loc,
                                           int32_t gtid)
{
    wasm::doOpenMPForStaticFini(loc, gtid);
}

static void __kmpc_for_static_init_4_wrapper(wasm_exec_env_t execEnv,
                                             int32_t loc,
                                             int32_t gtid,
                                             int32_t schedule,
                                             int32_t* lastIter,
                                             int32_t* lower,
                                             int32_t* upper,
                                             int32_t* stride,
                                             int32_t incr,
                                             int32_t chunk)
{
    wasm::doOpenMPForStaticInit4(
      loc, gtid, schedule, lastIter, lower, upper, stride, incr, chunk);
}

static void __kmpc_for_static_init_8_wrapper(wasm_exec_env_t execEnv,
                                             int32_t loc,
                                             int32_t gtid,
                                             int32_t schedule,
                                             int32_t* lastIter,
                                             int64_t* lower,
                                             int64_t* upper,
                                             int64_t* stride,
                                             int32_t incr,
                                             int32_t chunk)
{
    wasm::doOpenMPForStaticInit8(
      loc, gtid, schedule, lastIter, lower, upper, stride, incr, chunk);
}

static void __kmpc_fork_call_wrapper(wasm_exec_env_t execEnv,
                                     int32_t locPtr,
                                     int32_t nSharedVars,
                                     int32_t microTaskPtr,
                                     uint32_t* sharedVarsPtr)
{
    wasm::doOpenMPFork(locPtr, nSharedVars, microTaskPtr, sharedVarsPtr);
}

static int32_t __kmpc_global_thread_num_wrapper(wasm_exec_env_t exec_env,
                                                int32_t loc)
{
    return wasm::doOpenMPGlobalThreadNum(loc);
}

static int32_t __kmpc_master_wrapper(wasm_exec_env_t exec_env,
                                     int32_t loc,
                                     int32_t globalTid)
{
    return wasm::doOpenMPMaster(loc, globalTid);
}

static int32_t omp_get_num_threads_wrapper(wasm_exec_env_t exec_env)
{
    return wasm::doOpenMPGetNumThreads();
}

static int32_t omp_get_thread_num_wrapper(wasm_exec_env_t exec_env)
{
    return wasm::doOpenMPGetThreadNum();
}

static double omp_get_wtime_wrapper(wasm_exec_env_t exec_env)
{
    return wasm::doOpenMPGetWTime();
}

static void omp_set_num_threads_wrapper(wasm_exec_env_t exec_env,
                                        int32_t numThreads)
{
    wasm::doOpenMPSetNumThreads(numThreads);
}

static NativeSymbol ns[] = {
    REG_NATIVE_FUNC(__kmpc_barrier, "(ii)"),
    REG_NATIVE_FUNC(__kmpc_end_master, "(ii)"),
    REG_NATIVE_FUNC(__kmpc_for_static_fini, "(ii)"),
    REG_NATIVE_FUNC(__kmpc_for_static_init_4, "(iii****ii)"),
    REG_NATIVE_FUNC(__kmpc_for_static_init_8, "(iii****ii)"),
    REG_NATIVE_FUNC(__kmpc_fork_call, "(iiii)"),
    REG_NATIVE_FUNC(__kmpc_global_thread_num, "(i)i"),
    REG_NATIVE_FUNC(__kmpc_master, "(ii)i"),
    REG_NATIVE_FUNC(omp_get_num_threads, "()i"),
    REG_NATIVE_FUNC(omp_get_thread_num, "()i"),
    REG_NATIVE_FUNC(omp_get_wtime, "()F"),
    REG_NATIVE_FUNC(omp_set_num_threads, "(i)"),
};

uint32_t getFaasmOpenMPApi(NativeSymbol** nativeSymbols)
{
    *nativeSymbols = ns;
    return sizeof(ns) / sizeof(NativeSymbol);
}
}

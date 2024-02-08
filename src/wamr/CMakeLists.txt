# WARNING: the CMake flags and pre-processor definitions that we setin this
# file are carefully chosen for the WAMR build to run. Adding or removing flags
# may break Faasm.

# Set target platform details

# We must enable WAMR hardware bounds check here, otherwise WAMR uses malloc to
# allocate memory, which is not page-aligned. This seems like a blunt instrument
# to solve a smal problem, but this parameter is deeply embedded in the WAMR
# code, and it's difficult to change it surgically.
set(WAMR_DISABLE_HW_BOUND_CHECK 0)
# This definition prevents a buffer underflow during code generation
add_definitions(-DWASM_ENABLE_WAMR_COMPILER=1)
set(WAMR_BUILD_PLATFORM "linux")
set(WAMR_BUILD_INTERP 1)
set(WAMR_BUILD_AOT 1)
set(WAMR_BUILD_JIT 1)
set(WAMR_BUILD_DEBUG_INTERP 0)
set(WAMR_BUILD_DEBUG_AOT 0)
set(WAMR_BUILD_FAST_JIT 0)
set(WAMR_BUILD_WASI_NN 0)
set(WAMR_BUILD_LIBC_BUILTIN 1)
set(WAMR_BUILD_LIBC_WASI 1)
set(WAMR_BUILD_DUMP_CALL_STACK 1)
set(WAMR_BUILD_FAST_INTERP 0)
set(WAMR_BUILD_SHARED_MEMORY 1)
set(WAMR_BUILD_BULK_MEMORY 1)
set(WAMR_BUILD_REF_TYPES 0)
set(WAMR_BUILD_SIMD 1)
set(WAMR_BUILD_CUSTOM_NAME_SECTION 1)
set(WAMR_BUILD_CHECKPOINT_RESTORE 1)
set(WAMR_DISABLE_HW_BOUND_CHECK 1)

include(${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)
include_directories (${WAMR_ROOT_DIR}/../../ ${WAMR_ROOT_DIR}/../../include)
include_directories(${WAMR_ROOT_DIR}/../../include ${WAMR_ROOT_DIR}/core/shared/utils/uncommon/ ${WAMR_ROOT_DIR}/../../core/iwasm/aot ${WAMR_ROOT_DIR}/../../lib/yalantinglibs/include ${LLVM_INCLUDE_DIRS})
# 13/09/2021 - Setting the CMake flag includes the code required to run
# code generation, but the pre-processor macro introduces LLVM errors. It is
# safe to disable as we actually don't run JITed code.
remove_definitions("-DWASM_ENABLE_JIT=1")
add_definitions(-DWASM_ENABLE_WAMR_COMPILER=1)

# Disable WAMR warnings
# target_compile_options(wamrlib PRIVATE
#     -Wno-typedef-redefinition
#     -Wno-unused-command-line-argument
#     # We comment out some problematic LLVM code in WAMR. Commenting out triggers
#     # compilation warnings that we suppress
#     -Wno-ambiguous-reversed-operator
#     -Wno-unused-function
#     -Wno-deprecated-enum-enum-conversion
# )

# # -----------------------------
# # Faasm-specific configuration
# # -----------------------------

include_directories(${PLATFORM_SHARED_DIR})
include_directories(${WAMR_ROOT_DIR}/core/iwasm/include ${WAMR_ROOT_DIR}/core/iwasm/common ${WAMR_ROOT_DIR}/core/iwasm/libraries ${WAMR_ROOT_DIR}/core/iwasm/compilation ${WAMR_ROOT_DIR}/core/iwasm/aot ${WAMR_ROOT_DIR}/core/iwasm/interpreter ${WAMR_ROOT_DIR}/core/shared/utils ${WAMR_ROOT_DIR}/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/include/ ${WAMR_ROOT_DIR}/core/shared/platform/include)
# Link the specific LLVM libraries that WAMR needs
llvm_map_components_to_libnames(
    WAMR_LLVM_LIBRARIES
    core
    lto
    executionengine
    mcjit
)

# Link everything together
faasm_private_lib(wamrmodule
    WAMRWasmModule.cpp
    codegen.cpp
    dynlink.cpp
    env.cpp
    faasm.cpp
    filesystem.cpp
    memory.cpp
    mpi.cpp
    native.cpp
    process.cpp
    pthread.cpp
    signals.cpp
    state.cpp
    stubs.cpp
    timing.cpp
)
target_link_libraries(wamrmodule PUBLIC
    faasm::wasm
    faasm::wamrlib
    MVVM_export
    ${WAMR_LLVM_LIBRARIES}
)

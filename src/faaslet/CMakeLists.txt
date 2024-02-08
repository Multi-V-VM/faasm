
faasm_private_lib(faaslet_lib
    Faaslet.cpp
)
target_include_directories(faaslet_lib PRIVATE ${FAASM_INCLUDE_DIR}/faaslet ${WAMR_ROOT_DIR}/core/iwasm/include ${WAMR_ROOT_DIR}/core/iwasm/common ${WAMR_ROOT_DIR}/core/iwasm/libraries ${WAMR_ROOT_DIR}/core/iwasm/compilation ${WAMR_ROOT_DIR}/core/iwasm/aot ${WAMR_ROOT_DIR}/core/iwasm/interpreter ${WAMR_ROOT_DIR}/core/shared/utils ${WAMR_ROOT_DIR}/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/include/ ${WAMR_ROOT_DIR}/core/shared/platform/include)
target_link_libraries(faaslet_lib PUBLIC
    faasm::system
    faasm::threads
    faasm::storage
)

# Include SGX lib if enabled
if (NOT (FAASM_SGX_MODE STREQUAL "Disabled"))
    target_link_libraries(faaslet_lib PUBLIC faasm::enclave)
endif ()

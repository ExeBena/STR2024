cmake_minimum_required(VERSION 3.12)
# Name project
SET(ProjectName contador_cola)

# Set any variables required for importing libraries
SET(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)
set(FREERTOS_CONFIG_FILE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(FREERTOS_PORT GCC_RP2040)
# set(FREERTOS_HEAP 4)
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(${ProjectName}_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(${ProjectName}
${ProjectName}.c
)
pico_enable_stdio_usb(${ProjectName} 1)
# pico_enable_stdio_uart(${ProjectName} 1)
pico_add_extra_outputs(${ProjectName})

target_link_libraries(${ProjectName}
    pico_stdlib
    # hardware_uart
    # pico_time 
    FreeRTOS-Kernel-Heap4 
    # freertos_kernel
    )

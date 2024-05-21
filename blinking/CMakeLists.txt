cmake_minimum_required(VERSION 3.12)

# Name project
SET(ProjectName blinking)

# Set any variables required for importing libraries
SET(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)
set(FREERTOS_CONFIG_FILE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(FREERTOS_PORT GCC_RP2040)
set(FREERTOS_HEAP "4")

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName})

add_executable(${ProjectName}
${ProjectName}.c)
# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

pico_add_extra_outputs(${ProjectName})

target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    # freertos_kernel
    )


# Add subdirectories
# add_subdirectory(src)

# if you have anything in "lib" folder then uncomment below - remember to add a CMakeLists.txt
# file to the "lib" directory
#add_subdirectory(lib)
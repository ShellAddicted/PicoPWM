cmake_minimum_required(VERSION 3.12)

# Pull in Pico SDK (must be before project)
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

# Initialise the Pico SDK
pico_sdk_init()

add_library(PicoPWM INTERFACE)
target_sources(PicoPWM INTERFACE ${CMAKE_CURRENT_LIST_DIR}/picopwm.cpp)
target_include_directories(PicoPWM INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(PicoPWM INTERFACE pico_stdlib hardware_pwm)
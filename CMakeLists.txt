cmake_minimum_required(VERSION 3.13...3.27)

# initialize pico-sdk from submodule
# note: this must happen before project()
set(PICO_BOARD waveshare_rp2350_zero)
include(pico-sdk/pico_sdk_init.cmake)
project(rp2350-tree)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# project
add_executable(rp2350_tree
	src/main.c
)

target_link_libraries(rp2350_tree pico_stdlib pico_stdio_usb)

pico_add_extra_outputs(rp2350_tree)

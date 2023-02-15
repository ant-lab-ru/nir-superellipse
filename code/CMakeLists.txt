cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(nir-superellipse C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(nir-superellipse
  main.c
  bsp/hardware.c
  tasks/led-task.c
  tasks/display_task.c
  drivers/st7789-driver/st7789-driver.c
  drivers/st7789-driver/st7789-font.c
)

pico_enable_stdio_usb(nir-superellipse 1)
pico_enable_stdio_uart(nir-superellipse 0)

pico_add_extra_outputs(nir-superellipse)

target_link_libraries(nir-superellipse pico_stdlib hardware_spi)

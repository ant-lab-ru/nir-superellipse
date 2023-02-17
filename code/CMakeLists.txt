cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
project(nir-superellipse C CXX ASM)
pico_sdk_init()

set (DRIVERS
  drivers/st7789-driver/st7789-driver.c
  drivers/st7789-driver/st7789-font-default.c

  drivers/ws2812-driver/ws2812-driver.c
)

set (TASKS
  tasks/led-task.c
  tasks/display-task.c
  tasks/smart-led-task.c
)

add_executable(nir-superellipse
  main.c
  bsp/hardware.c
  ${TASKS}
  ${DRIVERS}
)

pico_enable_stdio_usb(nir-superellipse 1)
pico_enable_stdio_uart(nir-superellipse 0)

pico_add_extra_outputs(nir-superellipse)

target_link_libraries(nir-superellipse
  pico_stdlib
  hardware_spi
  hardware_pio
)

pico_generate_pio_header(nir-superellipse ${CMAKE_CURRENT_LIST_DIR}/bsp/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

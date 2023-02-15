#include "stdint.h"
#include "pico/stdlib.h"

#include "bsp/hardware.h"
#include "tasks/led-task.h"
#include "tasks/display_task.h"

#include "drivers/st7789-driver/st7789-driver.h"
#include "drivers/st7789-driver/st7789-colors.h"


int main() {

    stdio_init_all();
    init_hardware();

    st7789_init();
    st7789_fill_screen(ST7789_GREY_R050_G050_B050);

    while (1) {
        led_task();
        display_task();
    }
}
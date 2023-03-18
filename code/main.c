#include "stdint.h"
#include "pico/stdlib.h"

#include "main.h"
#include "bsp/hardware.h"
#include "tasks/led-task.h"
#include "tasks/logic-task.h"
#include "tasks/display-task.h"
#include "tasks/smart-led-task.h"

#include "deneg-lib/drivers/encoder-driver/include/encoder-driver.h"

struct Superellipse superellipse;

int main() {
    superellipse.state = STATE_MONOCHROME_RGB;

    superellipse.rgb_color.r = 0x70;
    superellipse.rgb_color.g = 0x70;
    superellipse.rgb_color.b = 0xFF;

    stdio_init_all();
    init_hardware();

    display_task_init();
    smart_led_task_init();

    st7789_set_brightness(&cdisp, 100);

    while (1) {
        led_task();
        encoder_task(&encoder0);
        encoder_task(&encoder1);
        encoder_task(&encoder2);

        logic_task();
        display_task();
        smart_led_task();
    }
}
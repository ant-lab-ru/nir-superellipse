#include "stdint.h"
#include "pico/stdlib.h"

#include "bsp/hardware.h"
#include "tasks/led-task.h"
#include "tasks/display-task.h"
#include "tasks/smart-led-task.h"


int main() {

    stdio_init_all();
    init_hardware();

    while (1) {
        led_task();
        display_task();
        smart_led_task();
    }
}
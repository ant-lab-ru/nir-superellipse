#include "led-task.h"
#include "pico/stdlib.h"
#include "stdint.h"
#include "../pins.h"

uint64_t timestamp_led = 0;

void led_task() {
    
    bool state = gpio_get(PIN_LED);
    uint64_t delay = state ? LED_TASK_ON_US : LED_TASK_OFF_US;

    if (time_us_64() - timestamp_led > delay) {
        gpio_put(PIN_LED, !state);
        timestamp_led = time_us_64();
    }
}
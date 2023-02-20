#include "smart-led-task.h"
#include "pico/stdlib.h"
#include "stdint.h"

#include "../drivers/ws2812-driver/ws2812-driver.h"
#include "../bsp/hardware.h"

uint64_t timestamp_smart_led = 0;
struct SmartLed {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t state;
    uint32_t t;
};

static struct SmartLed smart_led_colors = {
    .r = 0xff,
    .g = 0,
    .b = 0,
    .state = 1,
    .t = 0,
};

static uint8_t state = 0;

void smart_led_task() {
    switch(smart_led_colors.state){
    case 0: 
        if (time_us_64() - timestamp_smart_led > SMART_LED_TASK_PERIOD_US) {
            switch (state){
                case 0:
                    smart_led_colors.g++;
                    if (smart_led_colors.g == 0xff) state = 1;
                    break;
                case 1:
                    smart_led_colors.r--;
                    if (smart_led_colors.r == 0) state = 2;
                    break;
                case 2:
                    smart_led_colors.b++;
                    if (smart_led_colors.b == 0xff) state = 3;
                    break;
                case 3:
                    smart_led_colors.g--;
                    if (smart_led_colors.g == 0) state = 4;
                    break;
                case 4:
                    smart_led_colors.r++;
                    if (smart_led_colors.r == 0xff) state = 5;
                    break;
                case 5:
                    smart_led_colors.b--;
                    if (smart_led_colors.b == 0) state = 0;
                    break;
            }
            ws2812_monochrome(&ws, smart_led_colors.r, smart_led_colors.g, smart_led_colors.b);
            timestamp_smart_led = time_us_64();
        }
        break;
    case 1:
        if (time_us_64() - timestamp_smart_led > SMART_LED_TASK_SNAKES_PERIOD_US){
            smart_led_colors.t++;
            ws2812_pattern_snakes(&ws, smart_led_colors.t);
            timestamp_smart_led = time_us_64();
        }
        break;

    }
}
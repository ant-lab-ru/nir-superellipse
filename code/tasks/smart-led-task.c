#include "smart-led-task.h"
#include "pico/stdlib.h"
#include "stdint.h"
#include "stdbool.h"

#include "../drivers/ws2812-driver/ws2812-driver.h"
#include "../bsp/hardware.h"
#include "../pins.h"
#include "../main.h"

extern struct Superellipse superellipse;

uint64_t timestamp_smart_led = 0;

void smart_led_task() {

    ws2812_color_t color;
    switch (superellipse.state)
    {
        case STATE_MONOCHROME_RGB:;
            color.r = superellipse.rgb_color.r;
            color.g = superellipse.rgb_color.g;
            color.b = superellipse.rgb_color.b;
            ws2812_monochrome(&ws, color);
            sleep_ms(1);
            break;

        case STATE_BLINK:
        
            switch (superellipse.blink_mode) {
                case BLINK_MODE_WAVE:
                
                    break;
            }
            break;
    
        default:
            break;
    }
}

void smart_led_task_init() {
    ws2812_color_t color;
    color.r = superellipse.rgb_color.r;
    color.g = superellipse.rgb_color.g;
    color.b = superellipse.rgb_color.b;
    ws2812_monochrome(&ws, color);
}
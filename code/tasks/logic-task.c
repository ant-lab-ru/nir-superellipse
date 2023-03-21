#include "logic-task.h"

#include "../main.h"
#include "../bsp/hardware.h"

static uint32_t enc0_inc = 1;

void logic_task() {
    /* Logic for state update*/

    switch (superellipse.state) {
        case STATE_MONOCHROME_RGB:
            /* Red color */

            superellipse.rgb_color.r += (encsw0.spush * 0x20);
            encsw0.spush = 0;

            superellipse.rgb_color.r += encoder0.cw_counter;
            encoder0.cw_counter = 0;

            superellipse.rgb_color.r -= (encsw0.lpush * 0x20);
            encsw0.lpush = 0;

            superellipse.rgb_color.r -= encoder0.ccw_counter;
            encoder0.ccw_counter = 0;

            /* Green color */

            superellipse.rgb_color.g += (encsw1.spush * 0x20);
            encsw1.spush = 0;

            superellipse.rgb_color.g += encoder1.cw_counter;
            encoder1.cw_counter = 0;

            superellipse.rgb_color.g -= (encsw1.lpush * 0x20);
            encsw1.lpush = 0;

            superellipse.rgb_color.g -= encoder1.ccw_counter;
            encoder1.ccw_counter = 0;

            /* Blue color */
            
            superellipse.rgb_color.b += (encsw2.spush * 0x20);
            encsw2.spush = 0;

            superellipse.rgb_color.b += encoder2.cw_counter;
            encoder2.cw_counter = 0;

            superellipse.rgb_color.b -= (encsw2.lpush * 0x20);
            encsw2.lpush = 0;

            superellipse.rgb_color.b -= encoder2.ccw_counter;
            encoder2.ccw_counter = 0;

            break;
        
        case STATE_MONOCHROME_HSV:
            /* H */
            if ((uint32_t)encoder0.cw_counter + (uint32_t)superellipse.hsv_color.h >= 360 ) {
                superellipse.hsv_color.h = 360;
            }
            else {
                superellipse.hsv_color.h += encoder0.cw_counter;
            }
            encoder0.cw_counter = 0;

            if ((uint32_t)encoder0.ccw_counter >= (uint32_t)superellipse.hsv_color.h ) {
                superellipse.hsv_color.h = 0;
            }
            else {
                superellipse.hsv_color.h -= encoder0.ccw_counter;
            }
            encoder0.ccw_counter = 0;

            /* S */
            if ((uint32_t)encoder1.cw_counter + (uint32_t)superellipse.hsv_color.s >= 255 ) {
                superellipse.hsv_color.s = 255;
            }
            else {
                superellipse.hsv_color.s += encoder1.cw_counter;
            }
            encoder1.cw_counter = 0;

            if ((uint32_t)encoder1.ccw_counter >= (uint32_t)superellipse.hsv_color.s ) {
                superellipse.hsv_color.s = 0;
            }
            else {
                superellipse.hsv_color.s -= encoder1.ccw_counter;
            }
            encoder1.ccw_counter = 0;

            /* V */
            if ((uint32_t)encoder2.cw_counter + (uint32_t)superellipse.hsv_color.v >= 255 ) {
                superellipse.hsv_color.v = 255;
            }
            else {
                superellipse.hsv_color.v += encoder2.cw_counter;
            }
            encoder2.cw_counter = 0;

            if ((uint32_t)encoder2.ccw_counter >= (uint32_t)superellipse.hsv_color.v ) {
                superellipse.hsv_color.v;
            }
            else {
                superellipse.hsv_color.v -= encoder2.ccw_counter;
            }
            encoder2.ccw_counter = 0;
            break;

        case STATE_BLINK:
            if ((uint32_t)encoder1.cw_counter + (uint32_t)superellipse.blink_mode >= BLIND_MODE_END ) {
                superellipse.blink_mode = BLIND_MODE_END - 1;
            }
            else {
                superellipse.blink_mode += encoder1.cw_counter;
            }
            encoder1.cw_counter = 0;

            if ((uint32_t)encoder1.ccw_counter >= (uint32_t)superellipse.blink_mode ) {
                superellipse.blink_mode = 0;
            }
            else {
                superellipse.blink_mode -= encoder1.ccw_counter;
            }
            encoder1.ccw_counter = 0;
            break;
    }
}

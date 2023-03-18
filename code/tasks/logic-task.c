#include "logic-task.h"

#include "../main.h"
#include "../bsp/hardware.h"

void logic_task() {

    /* Logic for state update*/

    switch (superellipse.state) {
        case STATE_MONOCHROME_RGB:
            /* Red color */
            if ((uint32_t)encoder0.cw_counter + (uint32_t)superellipse.rgb_color.r >= 255 ) {
                superellipse.rgb_color.r = 255;
            }
            else {
                superellipse.rgb_color.r += encoder0.cw_counter;
            }
            encoder0.cw_counter = 0;

            if ((uint32_t)encoder0.ccw_counter >= (uint32_t)superellipse.rgb_color.r ) {
                superellipse.rgb_color.r = 0;
            }
            else {
                superellipse.rgb_color.r -= encoder0.ccw_counter;
            }
            encoder0.ccw_counter = 0;

            /* Green color */
            if ((uint32_t)encoder1.cw_counter + (uint32_t)superellipse.rgb_color.g >= 255 ) {
                superellipse.rgb_color.g = 255;
            }
            else {
                superellipse.rgb_color.g += encoder1.cw_counter;
            }
            encoder1.cw_counter = 0;

            if ((uint32_t)encoder1.ccw_counter >= (uint32_t)superellipse.rgb_color.g ) {
                superellipse.rgb_color.g = 0;
            }
            else {
                superellipse.rgb_color.g -= encoder1.ccw_counter;
            }
            encoder1.ccw_counter = 0;

            /* Blue color */
            if ((uint32_t)encoder2.cw_counter + (uint32_t)superellipse.rgb_color.b >= 255 ) {
                superellipse.rgb_color.b = 255;
            }
            else {
                superellipse.rgb_color.b += encoder2.cw_counter;
            }
            encoder2.cw_counter = 0;

            if ((uint32_t)encoder2.ccw_counter >= (uint32_t)superellipse.rgb_color.b ) {
                superellipse.rgb_color.b = 0;
            }
            else {
                superellipse.rgb_color.b -= encoder2.ccw_counter;
            }
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

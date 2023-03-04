#include "logic-task.h"

#include "../main.h"
#include "../bsp/hardware.h"

void logic_task() {
    /* Red color */
    if ((uint32_t)encoder0.cw_counter + (uint32_t)superellipse.color.r >= 255 ) {
        superellipse.color.r = 255;
    }
    else {
        superellipse.color.r += encoder0.cw_counter;
    }
    encoder0.cw_counter = 0;

    if ((uint32_t)encoder0.ccw_counter >= (uint32_t)superellipse.color.r ) {
        superellipse.color.r = 0;
    }
    else {
        superellipse.color.r -= encoder0.ccw_counter;
    }
    encoder0.ccw_counter = 0;

    /* Green color */
    if ((uint32_t)encoder0.cw_counter + (uint32_t)superellipse.color.g >= 255 ) {
        superellipse.color.g = 255;
    }
    else {
        superellipse.color.g += encoder0.cw_counter;
    }
    encoder0.cw_counter = 0;

    if ((uint32_t)encoder0.ccw_counter >= (uint32_t)superellipse.color.g ) {
        superellipse.color.g = 0;
    }
    else {
        superellipse.color.g -= encoder0.ccw_counter;
    }
    encoder0.ccw_counter = 0;

    /* Blue color */
    if ((uint32_t)encoder0.cw_counter + (uint32_t)superellipse.color.b >= 255 ) {
        superellipse.color.b = 255;
    }
    else {
        superellipse.color.b += encoder0.cw_counter;
    }
    encoder0.cw_counter = 0;

    if ((uint32_t)encoder0.ccw_counter >= (uint32_t)superellipse.color.b ) {
        superellipse.color.b = 0;
    }
    else {
        superellipse.color.b -= encoder0.ccw_counter;
    }
    encoder0.ccw_counter = 0;
}

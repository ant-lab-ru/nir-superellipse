#include "display-task.h"
#include "../drivers/st7789-driver/st7789-driver.h"
#include "../drivers/st7789-driver/st7789-colors.h"
#include "../bsp/hardware.h"

#include "pico/stdlib.h"

uint64_t timestamp_display = 0;
static struct DisplayTask {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    uint8_t r_prev;
    uint8_t g_prev;
    uint8_t b_prev;
} diplay_task;

void display_task() {
    if (time_us_64() - timestamp_display > DISPLAY_TASK_PERIOD_US) {

        // letter = encoder0.cw_counter - encoder0.ccw_counter;

        if (diplay_task.r != diplay_task.r_prev) {
            diplay_task.r_prev = diplay_task.r;
            st7789_letter(&ldisp, diplay_task.r / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
            st7789_letter(&ldisp, diplay_task.r % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
        }

        if (diplay_task.g != diplay_task.g_prev) {
            diplay_task.g_prev = diplay_task.g;
            st7789_letter(&cdisp, diplay_task.g / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_GREEN_R165_G255_B165, "default");
            st7789_letter(&cdisp, diplay_task.g % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_GREEN_R165_G255_B165, "default");
        }

        if (diplay_task.b != diplay_task.b_prev) {
            diplay_task.b_prev = diplay_task.b;
            st7789_letter(&rdisp, diplay_task.b / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_BLUE_R165_G165_B255, "default");
            st7789_letter(&rdisp, diplay_task.b % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_BLUE_R165_G165_B255, "default");
        }

        timestamp_display = time_us_64();
    }
}

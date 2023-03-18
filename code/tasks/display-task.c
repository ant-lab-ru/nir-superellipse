#include "display-task.h"
#include "../drivers/st7789-driver/st7789-driver.h"
#include "../drivers/st7789-driver/st7789-colors.h"
#include "../bsp/hardware.h"
#include "../main.h"

#include "pico/stdlib.h"

static uint64_t timestamp_display = 0;

extern struct Superellipse superellipse;

struct RGB disp_prev_color = {
    .r = 0,
    .g = 0,
    .b = 0,
};

void display_task() {

    switch (superellipse.state) {
        case STATE_MONOCHROME_RGB:
            if (time_us_64() - timestamp_display > DISPLAY_TASK_PERIOD_US) {
                if (superellipse.rgb_color.r != disp_prev_color.r) {
                    disp_prev_color.r = superellipse.rgb_color.r;
                    st7789_letter(&ldisp, superellipse.rgb_color.r / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
                    st7789_letter(&ldisp, superellipse.rgb_color.r % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
                }

                if (superellipse.rgb_color.g != disp_prev_color.g) {
                    disp_prev_color.g = superellipse.rgb_color.g;
                    st7789_letter(&cdisp, superellipse.rgb_color.g / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_GREEN_R165_G255_B165, "default");
                    st7789_letter(&cdisp, superellipse.rgb_color.g % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_GREEN_R165_G255_B165, "default");
                }

                if (superellipse.rgb_color.b != disp_prev_color.b) {
                    disp_prev_color.b = superellipse.rgb_color.b;
                    st7789_letter(&rdisp, superellipse.rgb_color.b / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_BLUE_R165_G165_B255, "default");
                    st7789_letter(&rdisp, superellipse.rgb_color.b % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_BLUE_R165_G165_B255, "default");
                }

                timestamp_display = time_us_64();
            }
            break;
    }
}

void display_task_init() {
    st7789_fill_screen(&ldisp, ST7789_RED_R255_G165_B165);
    st7789_fill_screen(&cdisp, ST7789_GREEN_R165_G255_B165);
    st7789_fill_screen(&rdisp, ST7789_BLUE_R165_G165_B255);

    st7789_letter(&ldisp, superellipse.rgb_color.r / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    st7789_letter(&ldisp, superellipse.rgb_color.r % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    disp_prev_color.r = superellipse.rgb_color.r;

    st7789_letter(&cdisp, superellipse.rgb_color.g / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_GREEN_R165_G255_B165, "default");
    st7789_letter(&cdisp, superellipse.rgb_color.g % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_GREEN_R165_G255_B165, "default");
    disp_prev_color.g = superellipse.rgb_color.g;

    st7789_letter(&rdisp, superellipse.rgb_color.b / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_BLUE_R165_G165_B255, "default");
    st7789_letter(&rdisp, superellipse.rgb_color.b % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_BLUE_R165_G165_B255, "default");
    disp_prev_color.b = superellipse.rgb_color.b;

    timestamp_display = time_us_64();
}


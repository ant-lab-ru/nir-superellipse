#include "display-task.h"
#include "../drivers/st7789-driver/st7789-driver.h"
#include "../drivers/st7789-driver/st7789-colors.h"
#include "../bsp/hardware.h"
#include "../main.h"

#include "pico/stdlib.h"

static uint64_t timestamp_display = 0;

extern struct Superellipse superellipse;

struct Color disp_prev_color = {
    .r = 0,
    .g = 0,
    .b = 0,
};

void display_task() {
    if (time_us_64() - timestamp_display > DISPLAY_TASK_PERIOD_US) {

        if (superellipse.color.r != disp_prev_color.r) {
            disp_prev_color.r = superellipse.color.r;
            st7789_letter(&ldisp, superellipse.color.r / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
            st7789_letter(&ldisp, superellipse.color.r % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
        }

        if (superellipse.color.g != disp_prev_color.g) {
            disp_prev_color.g = superellipse.color.g;
            st7789_letter(&cdisp, superellipse.color.g / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
            st7789_letter(&cdisp, superellipse.color.g % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
        }

        if (superellipse.color.b != disp_prev_color.b) {
            disp_prev_color.b = superellipse.color.b;
            st7789_letter(&rdisp, superellipse.color.b / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
            st7789_letter(&rdisp, superellipse.color.b % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
        }

        timestamp_display = time_us_64();
    }
}

void display_task_init() {
    st7789_fill_screen(&ldisp, ST7789_GREEN_R165_G255_B165);
    st7789_fill_screen(&cdisp, ST7789_GREEN_R165_G255_B165);
    st7789_fill_screen(&rdisp, ST7789_GREEN_R165_G255_B165);

    st7789_letter(&ldisp, superellipse.color.r / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    st7789_letter(&ldisp, superellipse.color.r % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    disp_prev_color.r = superellipse.color.r;

    st7789_letter(&cdisp, superellipse.color.g / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    st7789_letter(&cdisp, superellipse.color.g % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    disp_prev_color.g = superellipse.color.g;

    st7789_letter(&rdisp, superellipse.color.b / 16, 3, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    st7789_letter(&rdisp, superellipse.color.b % 16, 118, 40, ST7789_GREY_R050_G050_B050, ST7789_RED_R255_G165_B165, "default");
    disp_prev_color.b = superellipse.color.b;

    timestamp_display = time_us_64();
}


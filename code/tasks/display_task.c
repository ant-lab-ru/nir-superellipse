#include "display_task.h"
#include "../drivers/st7789-driver/st7789-driver.h"
#include "../drivers/st7789-driver/st7789-colors.h"
#include "../bsp/hardware.h"

#include "pico/stdlib.h"

uint64_t timestamp_display = 0;
uint8_t letter = 0;

void display_task() {
    if (time_us_64() - timestamp_display > DISPLAY_TASK_PERIOD_US) {

        st7789_letter(&display_spi_ctx, letter / 16, 3, 25, ST7789_GREEN_R165_G255_B165, ST7789_GREY_R050_G050_B050, "default");
        st7789_letter(&display_spi_ctx, letter % 16, 118, 25, ST7789_GREEN_R165_G255_B165, ST7789_GREY_R050_G050_B050, "default");

        letter++;
        timestamp_display = time_us_64();
    }
}

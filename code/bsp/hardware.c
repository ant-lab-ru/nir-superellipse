// SDK includes
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pio.h"

#include "stdint.h"

#include "../generated/ws2812.pio.h"

// My includes
#include "../pins.h"
#include "../cfgs.h"
#include "hardware.h"

st7789_driver_t cdisp;
ws2812_driver_t ws;


/**
 * @brief Init GPIO pins
 * 
 * PIN_LED sets to output
 */
void init_gpio() {

    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    gpio_init(PIN_ST7789_DC);
    gpio_set_dir(PIN_ST7789_DC, GPIO_OUT);

    gpio_init(PIN_ST7789_RST);
    gpio_set_dir(PIN_ST7789_RST, GPIO_OUT);

    gpio_init(PIN_ST7789_BLK);
    gpio_set_dir(PIN_ST7789_BLK, GPIO_OUT);

    gpio_init(PIN_ST7789_CS);
    gpio_set_dir(PIN_ST7789_CS, GPIO_OUT);
}

/**
 * @brief Init SPI perif and pins for SPI
 * 
 */
void init_spi() {
    spi_init(DISPLAY_SPI, DISPLAY_SPI_SPEED);
    gpio_set_function(PIN_ST7789_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_ST7789_CLK,  GPIO_FUNC_SPI);
}

void init_pio() {
    uint offset = pio_add_program(WS2812_PIO, &ws2812_program);
    ws2812_program_init(WS2812_PIO, WS2812_PIO_SM, offset, PIN_WS2812_CH1, 800000, false);
}

void put_pixel_rgb(uint8_t r, uint8_t g, uint8_t b) {
    uint32_t pixel = 0;
    pixel |= (g << 24);
    pixel |= (r << 16);
    pixel |= (b << 8);
    pio_sm_put_blocking(WS2812_PIO, WS2812_PIO_SM, pixel);
}

void pwm_set_perc (uint8_t* val) {
    // !FIXME
    gpio_put(PIN_ST7789_BLK, 1);
}

void spi_display_w (const uint8_t* data, uint32_t size) {
    spi_write_blocking(DISPLAY_SPI, data, size);
}

void gpio_cs_set() {
    gpio_put(PIN_ST7789_CS, 1);
}

void gpio_cs_reset() {
    gpio_put(PIN_ST7789_CS, 0);
}

void gpio_dc_set() {
    gpio_put(PIN_ST7789_DC, 1);
}

void gpio_dc_reset() {
    gpio_put(PIN_ST7789_DC, 0);
}

void gpio_rst_set() {
    gpio_put(PIN_ST7789_RST, 1);
}

void gpio_rst_reset() {
    gpio_put(PIN_ST7789_RST, 0);
}

void delay_us(uint64_t time_us) {
    sleep_us(time_us);
}

void init_cdisp() {
    cdisp.public.spi_w = spi_display_w;
    cdisp.public.cs_set = gpio_cs_set;
    cdisp.public.cs_reset = gpio_cs_reset;
    cdisp.public.dc_set = gpio_dc_set;
    cdisp.public.dc_reset = gpio_dc_reset;
    cdisp.public.rst_set = gpio_rst_set;
    cdisp.public.rst_reset = gpio_rst_reset;
    cdisp.public.delay_us = sleep_us;
    cdisp.public.set_brightness = pwm_set_perc;
}

void init_ws () {
    ws.len  = WS2812_LEN;
    ws.w    = put_pixel_rgb;
}

void init_hardware() {

    init_gpio();
    init_spi();
    init_pio();

    init_cdisp();
    st7789_init(&cdisp);
    st7789_fill_screen(&cdisp, ST7789_GREY_R050_G050_B050);

    init_ws();
    ws2812_monochrome(&ws, 0, 0, 0);
}
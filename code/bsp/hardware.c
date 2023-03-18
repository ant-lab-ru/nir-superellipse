// SDK includes
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/pio.h"

#include "stdint.h"

#include "../generated/ws2812.pio.h"

// My includes
#include "../pins.h"
#include "../cfgs.h"
#include "../main.h"
#include "hardware.h"

st7789_driver_t cdisp;
st7789_driver_t rdisp;
st7789_driver_t ldisp;
ws2812_driver_t ws;

encoder_ctx_t encoder0;
encoder_ctx_t encoder1;
encoder_ctx_t encoder2;

uint16_t disp_buffer [ST7789_WIDTH * ST7789_HEIGHT];


/**
 * @brief Init GPIO pins
 * 
 * PIN_LED sets to output
 */
void init_gpio() {

    // Del this!!!!!
    gpio_init(0);
    gpio_set_dir(0, GPIO_OUT);
    gpio_put(0, 1);
    // End of Del 

    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    gpio_init(PIN_ST7789_DC);
    gpio_set_dir(PIN_ST7789_DC, GPIO_OUT);

    gpio_init(PIN_ST7789_RST0);
    gpio_set_dir(PIN_ST7789_RST0, GPIO_OUT);

    gpio_init(PIN_ST7789_RST1);
    gpio_set_dir(PIN_ST7789_RST1, GPIO_OUT);

    gpio_init(PIN_ST7789_RST2);
    gpio_set_dir(PIN_ST7789_RST2, GPIO_OUT);

    gpio_init(PIN_ST7789_BLK);
    gpio_set_dir(PIN_ST7789_BLK, GPIO_OUT);
    gpio_put(PIN_ST7789_BLK, 0);

    gpio_init(PIN_ST7789_CS0);
    gpio_set_dir(PIN_ST7789_CS0, GPIO_OUT);

    gpio_init(PIN_ST7789_CS1);
    gpio_set_dir(PIN_ST7789_CS1, GPIO_OUT);

    gpio_init(PIN_ST7789_CS2);
    gpio_set_dir(PIN_ST7789_CS2, GPIO_OUT);

    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_up(PIN_BUTTON);

    gpio_init(PIN_ENCODER0_A);
    gpio_set_dir(PIN_ENCODER0_A, GPIO_IN);
    gpio_pull_up(PIN_ENCODER0_A);

    gpio_init(PIN_ENCODER0_B);
    gpio_set_dir(PIN_ENCODER0_B, GPIO_IN);
    gpio_pull_up(PIN_ENCODER0_B);

    gpio_init(PIN_ENCODER1_A);
    gpio_set_dir(PIN_ENCODER1_A, GPIO_IN);
    gpio_pull_up(PIN_ENCODER1_A);

    gpio_init(PIN_ENCODER1_B);
    gpio_set_dir(PIN_ENCODER1_B, GPIO_IN);
    gpio_pull_up(PIN_ENCODER1_B);

    gpio_init(PIN_ENCODER2_A);
    gpio_set_dir(PIN_ENCODER2_A, GPIO_IN);
    gpio_pull_up(PIN_ENCODER2_A);

    gpio_init(PIN_ENCODER2_B);
    gpio_set_dir(PIN_ENCODER2_B, GPIO_IN);
    gpio_pull_up(PIN_ENCODER2_B);

    gpio_init(PIN_ENCODER0_SW);
    gpio_set_dir(PIN_ENCODER0_SW, GPIO_IN);
    gpio_pull_up(PIN_ENCODER0_SW);

    gpio_init(PIN_ENCODER1_SW);
    gpio_set_dir(PIN_ENCODER1_SW, GPIO_IN);
    gpio_pull_up(PIN_ENCODER1_SW);

    gpio_init(PIN_ENCODER2_SW);
    gpio_set_dir(PIN_ENCODER2_SW, GPIO_IN);
    gpio_pull_up(PIN_ENCODER2_SW);
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
    ws2812_program_init(WS2812_PIO, WS2812_PIO_SM, offset, PIN_WS2812, 800000, false);
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
    if (*val > 0) {
        gpio_put(PIN_ST7789_BLK, 1);
    }
    else {
        gpio_put(PIN_ST7789_BLK, 0);
    }
}

void spi_display_w (const uint8_t* data, uint32_t size) {
    spi_write_blocking(DISPLAY_SPI, data, size);
}

void gpio_cs0_set() {
    gpio_put(PIN_ST7789_CS0, 1);
}

void gpio_cs0_reset() {
    gpio_put(PIN_ST7789_CS0, 0);
}

void gpio_cs1_set() {
    gpio_put(PIN_ST7789_CS1, 1);
}

void gpio_cs1_reset() {
    gpio_put(PIN_ST7789_CS1, 0);
}

void gpio_cs2_set() {
    gpio_put(PIN_ST7789_CS2, 1);
}

void gpio_cs2_reset() {
    gpio_put(PIN_ST7789_CS2, 0);
}

void gpio_dc_set() {
    gpio_put(PIN_ST7789_DC, 1);
}

void gpio_dc_reset() {
    gpio_put(PIN_ST7789_DC, 0);
}

void gpio_rst0_set() {
    gpio_put(PIN_ST7789_RST0, 1);
}

void gpio_rst0_reset() {
    gpio_put(PIN_ST7789_RST0, 0);
}

void gpio_rst1_set() {
    gpio_put(PIN_ST7789_RST1, 1);
}

void gpio_rst1_reset() {
    gpio_put(PIN_ST7789_RST1, 0);
}

void gpio_rst2_set() {
    gpio_put(PIN_ST7789_RST2, 1);
}

void gpio_rst2_reset() {
    gpio_put(PIN_ST7789_RST2, 0);
}

void delay_us(uint64_t time_us) {
    sleep_us(time_us);
}
bool gpio_get_enc0_a() {
    return gpio_get(PIN_ENCODER0_A);
}
bool gpio_get_enc0_b() {
    return gpio_get(PIN_ENCODER0_B);
}
bool gpio_get_enc1_a() {
    return gpio_get(PIN_ENCODER1_A);
}
bool gpio_get_enc1_b() {
    return gpio_get(PIN_ENCODER1_B);
}
bool gpio_get_enc2_a() {
    return gpio_get(PIN_ENCODER2_A);
}
bool gpio_get_enc2_b() {
    return gpio_get(PIN_ENCODER2_B);
}

void init_cdisp() {
    cdisp.public.spi_w = spi_display_w;
    cdisp.public.cs_set = gpio_cs1_set;
    cdisp.public.cs_reset = gpio_cs1_reset;
    cdisp.public.dc_set = gpio_dc_set;
    cdisp.public.dc_reset = gpio_dc_reset;
    cdisp.public.rst_set = gpio_rst1_set;
    cdisp.public.rst_reset = gpio_rst1_reset;
    cdisp.public.delay_us = sleep_us;
    cdisp.public.set_brightness = pwm_set_perc;
}

void init_rdisp() {
    rdisp.public.spi_w = spi_display_w;
    rdisp.public.cs_set = gpio_cs2_set;
    rdisp.public.cs_reset = gpio_cs2_reset;
    rdisp.public.dc_set = gpio_dc_set;
    rdisp.public.dc_reset = gpio_dc_reset;
    rdisp.public.rst_set = gpio_rst2_set;
    rdisp.public.rst_reset = gpio_rst2_reset;
    rdisp.public.delay_us = sleep_us;
    rdisp.public.set_brightness = pwm_set_perc;
}

void init_ldisp() {
    ldisp.public.spi_w = spi_display_w;
    ldisp.public.cs_set = gpio_cs0_set;
    ldisp.public.cs_reset = gpio_cs0_reset;
    ldisp.public.dc_set = gpio_dc_set;
    ldisp.public.dc_reset = gpio_dc_reset;
    ldisp.public.rst_set = gpio_rst0_set;
    ldisp.public.rst_reset = gpio_rst0_reset;
    ldisp.public.delay_us = sleep_us;
    ldisp.public.set_brightness = pwm_set_perc;
}

void blink_led() {
    bool st = gpio_get(PIN_LED);
    gpio_put(PIN_LED, !st);
}

void init_hardware() {

    init_gpio();
    init_spi();
    init_pio();

    init_cdisp();
    st7789_init(&cdisp, &disp_buffer);

    init_rdisp();
    st7789_init(&rdisp, &disp_buffer);

    init_ldisp();
    st7789_init(&ldisp, &disp_buffer);

    ws2812_init(&ws, put_pixel_rgb, WS2812_LEN);
    ws2812_off(&ws);

    encoder_init(&encoder0, time_us_64, gpio_get_enc0_a, false, gpio_get_enc0_b, false, false);
    encoder_init(&encoder1, time_us_64, gpio_get_enc1_a, false, gpio_get_enc1_b, false, false);
    encoder_init(&encoder2, time_us_64, gpio_get_enc2_a, false, gpio_get_enc2_b, false, false);
}
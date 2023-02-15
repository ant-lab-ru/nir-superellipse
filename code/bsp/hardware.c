// SDK includes
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "stdint.h"

// My includes
#include "../pins.h"
#include "../cfgs.h"
#include "hardware.h"

#include "../drivers/st7789-driver/st7789-driver.h"

spi_ctx_t display_spi_ctx;

st7789_driver_t st7789_driver;

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
    display_spi_ctx.spix    = DISPLAY_SPI;
    display_spi_ctx.bitrate = DISPLAY_SPI_SPEED;

    spi_init(display_spi_ctx.spix, display_spi_ctx.bitrate);
    gpio_set_function(PIN_ST7789_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_ST7789_CLK,  GPIO_FUNC_SPI);

    display_spi_ctx.write = spi_write_blocking;
}

void pwm_set_perc (const void* ctx, uint8_t* val) {
    // !FIXME
    gpio_put(PIN_ST7789_BLK, 1);
}
void spi_w (const void* ctx, uint8_t* data, uint32_t size) {
    spi_ctx_t* cctx = (spi_ctx_t*) ctx;
    cctx->write(cctx->spix, data, size);
}
void gpio_cs_set(const void* ctx) {
    gpio_put(PIN_ST7789_CS, 1);
}
void gpio_cs_reset(const void* ctx) {
    gpio_put(PIN_ST7789_CS, 0);
}
void gpio_dc_set(const void* ctx) {
    gpio_put(PIN_ST7789_DC, 1);
}
void gpio_dc_reset(const void* ctx) {
    gpio_put(PIN_ST7789_DC, 0);
}
void gpio_rst_set(const void* ctx) {
    gpio_put(PIN_ST7789_RST, 1);
}
void gpio_rst_reset(const void* ctx) {
    gpio_put(PIN_ST7789_RST, 0);
}
void delay_us(const void* ctx, uint64_t time_us) {
    sleep_us(time_us);
}

void init_display_driver() {
    st7789_driver.spi_w     = spi_w;
    st7789_driver.cs_set    = gpio_cs_set;
    st7789_driver.cs_reset  = gpio_cs_reset;
    st7789_driver.dc_set    = gpio_dc_set;
    st7789_driver.dc_reset  = gpio_dc_reset;
    st7789_driver.rst_set   = gpio_rst_set;
    st7789_driver.rst_reset = gpio_rst_reset;
    st7789_driver.set_brightness = pwm_set_perc;
    st7789_driver.delay_us          = delay_us;
}

void init_hardware() {

    init_gpio();
    init_spi();

    init_display_driver();
}
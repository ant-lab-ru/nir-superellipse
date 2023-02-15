// SDK includes
#include "hardware/gpio.h"
#include "hardware/spi.h"

// My includes
#include "../pins.h"
#include "../cfgs.h"
#include "hardware.h"


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

void init_hardware() {

    init_gpio();
    init_spi();
}

#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "hardware/spi.h"
#include "../drivers/st7789-driver/st7789-driver.h"
#include "../drivers/ws2812-driver/ws2812-driver.h"

extern st7789_driver_t cdisp;
extern ws2812_driver_t ws;

void init_hardware();
void put_pixel(uint32_t pixel_grb);

#endif // #ifndef __HARDWARE_H
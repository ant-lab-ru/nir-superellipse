#ifndef __WS2812_DRIVER_H
#define __WS2812_DRIVER_H

#include "stdint.h"

typedef void (*write_rgb_pixel) (uint8_t r, uint8_t g, uint8_t b);

typedef struct
{
    write_rgb_pixel w;
    uint32_t len;

} ws2812_driver_t;

// Functions
void ws2812_monochrome (ws2812_driver_t* ws_ctx, uint8_t r, uint8_t g, uint8_t b);
void ws2812_pattern_snakes (ws2812_driver_t* ws_ctx, uint32_t t);
void ws2812_pattern_greys (ws2812_driver_t* ws_ctx, uint32_t t);


#endif // #ifndef __WS2812_DRIVER_H
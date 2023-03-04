#ifndef __WS2812_DRIVER_H
#define __WS2812_DRIVER_H

#include "stdint.h"


typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ws2812_color_t;

typedef struct {
    uint16_t h;
    uint8_t  s;
    uint8_t  v;
} ws2812_hsv_t;

typedef void (*write_rgb_pixel) (uint8_t r, uint8_t g, uint8_t b);

typedef struct
{
    write_rgb_pixel w;
    uint32_t len;

} ws2812_driver_t;

// Functions
void ws2812_off (ws2812_driver_t* ws_ctx);
void ws2812_monochrome (ws2812_driver_t* ws_ctx, ws2812_color_t rgb888);
void ws2812_monochrome_slice (ws2812_driver_t* ws_ctx, ws2812_color_t rgb888, uint32_t first, uint32_t last);


void ws2812_pattern_snakes (ws2812_driver_t* ws_ctx, uint32_t t);
void ws2812_pattern_greys (ws2812_driver_t* ws_ctx, uint32_t t);


#endif // #ifndef __WS2812_DRIVER_H
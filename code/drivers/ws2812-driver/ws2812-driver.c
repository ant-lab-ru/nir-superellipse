#include "ws2812-driver.h"

void ws2812_monochrome (ws2812_driver_t* ws_ctx, uint8_t r, uint8_t g, uint8_t b) {
    for (uint32_t i = 0; i < ws_ctx->len; i++) {
        ws_ctx->w(r, g, b);
    }
}

void ws2812_pattern_snakes (ws2812_driver_t* ws_ctx, uint32_t t) {
    for (uint32_t i = 0; i < ws_ctx->len; i++) {
        uint32_t x = (i + (t >> 1)) % 64;
        if (x < 10)
            ws_ctx->w(0xff, 0, 0);
        else if (x >= 15 && x < 25)
            ws_ctx->w(0, 0xff, 0);
        else if (x >= 30 && x < 40)
            ws_ctx->w(0, 0, 0xff);
        else
            ws_ctx->w(0, 0, 0);
    }
}

void ws2812_pattern_greys (ws2812_driver_t* ws_ctx, uint32_t t) {
    int max = 100;
    t %= max;
    for (int i = 0; i < ws_ctx->len; i++) {
        ws_ctx->w(t, t, t);
        if (++t >= max) {
            t = 0;
        }
    }
}

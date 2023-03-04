#include "ws2812-driver.h"

static void ws2812_hsv_to_rgb (ws2812_hsv_t hsv, ws2812_color_t* rgb) {
    uint8_t r = 0, g = 0, b = 0;

	if (hsv.s == 0) {
		r = hsv.v;
		g = hsv.v;
		b = hsv.v;
	}
	else {
		uint32_t hi, a, vmin, vinc, vdec;

		if (hsv.h >= 360) {
			hsv.h = 0;
        }

		hi = (hsv.h / 60) % 6;
        vmin = (100 - hsv.s) * hsv.v / 100;
        a = (hsv.v - vmin) * (hsv.h % 60) / 60;
        vinc = vmin + a;
        vdec = hsv.v - a;

		switch (hi) {
		case 0:
			r = hsv.v;
			g = vinc;
			b = vmin;
			break;

		case 1:
			r = vdec;
			g = hsv.v;
			b = vmin;
			break;

		case 2:
			r = vmin;
			g = hsv.v;
			b = vinc;
			break;

		case 3:
			r = vmin;
			g = vdec;
			b = hsv.v;
			break;

		case 4:
			r = vinc;
			g = vmin;
			b = hsv.v;
			break;

		default:
			r = hsv.v;
			g = vmin;
			b = vdec;
			break;
		}
	}
    rgb->r = r;
    rgb->g = g;
    rgb->b = b;
}

void ws2812_monochrome (ws2812_driver_t* ws_ctx, ws2812_color_t rgb888) {
    for (uint32_t i = 0; i < ws_ctx->len; i++) {
        ws_ctx->w(rgb888.r, rgb888.g, rgb888.b);
    }
}

void ws2812_off (ws2812_driver_t* ws_ctx) {
    ws2812_color_t color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    ws2812_monochrome(ws_ctx, color);
}

void ws2812_monochrome_hsv (ws2812_driver_t* ws_ctx, ws2812_hsv_t hsv) {
    ws2812_color_t rgb;
    ws2812_hsv_to_rgb(hsv, &rgb);
    for (uint32_t i = 0; i < ws_ctx->len; i++) {
        ws_ctx->w(rgb.r, rgb.g, rgb.b);
    }
}

void ws2812_monochrome_slice_hsv (ws2812_driver_t* ws_ctx, ws2812_hsv_t hsv, uint32_t first, uint32_t last) {
    ws2812_color_t rgb;
    ws2812_hsv_to_rgb(hsv, &rgb);
    if (first > last) {
        first = last;
    }
    uint32_t str = (first >= ws_ctx->len) ? ws_ctx->len : first;
    uint32_t end = (last  >= ws_ctx->len) ? ws_ctx->len : last;

    for (uint32_t i = 0; i <= end; i++) {
        if (i >= str) {
            ws_ctx->w(rgb.r, rgb.g, rgb.b);
        }
        else {
            ws_ctx->w(0, 0, 0);
        }
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

void ws2812_pattern_wave (ws2812_driver_t* ws_ctx, ws2812_hsv_t base, uint32_t t) {
    ws2812_color_t c;
    ws2812_hsv_t hsv = base;
    for (uint32_t i = 0; i < ws_ctx->len; i++) {
        uint32_t x = (i + (t >> 1)) % 64;
        
        if (x < 15) {
            hsv.h = base.h + x * 24;
        }
        else {
            hsv.h = base.h;
        }
        ws2812_hsv_to_rgb(hsv, &c);
        ws_ctx->w(c.r, c.g, c.b);
    }
}



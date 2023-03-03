#ifndef __ST7789_DRIVER_H
#define __ST7789_DRIVER_H

#include "stdint.h"
#include "st7789-colors.h"

#define ST7789_WIDTH 240
#define ST7789_HEIGHT 280

typedef void (*st7789_spi_w)  	(const uint8_t*, uint32_t);
typedef void (*st7789_pwm_rw)   (uint8_t*);
typedef void (*st7789_delay_us) (uint64_t);
typedef void (*st7789_gpio_put) ();

typedef struct {
	st7789_spi_w	spi_w;

	st7789_gpio_put	cs_set;
	st7789_gpio_put	cs_reset;

	st7789_gpio_put	dc_set;
	st7789_gpio_put	dc_reset;

	st7789_gpio_put	rst_set;
	st7789_gpio_put	rst_reset;

	st7789_pwm_rw  	set_brightness;

	st7789_delay_us delay_us;

} st7789_driver_public_t;


typedef struct {
	const char* name;
	uint16_t width;
	uint16_t height;
	const uint8_t* data;
} st7789_font_t;

typedef struct {
	// Public
	st7789_driver_public_t public;

	// Private
	uint8_t rotation;
	uint16_t (*buffer)[ST7789_WIDTH * ST7789_HEIGHT];

	st7789_font_t* fonts[32];
	uint8_t fonts_number;

	uint8_t brightness;

} st7789_driver_t;

#define ST7789_DEFAULT_ROTATION  	2
#define ST7789_DEFAULT_BRIGHTNESS 	0
#define ST7789_DEFAULT_COLOR  		ST7789_BLACK

void st7789_init(st7789_driver_t* st_ctx, uint16_t (*buffer)[ST7789_WIDTH * ST7789_HEIGHT]);
void st7789_set_rotation (st7789_driver_t* st_ctx, uint8_t m);
void st7789_fill_screen (st7789_driver_t* st_ctx, uint16_t color);
void st7789_set_brightness (st7789_driver_t* st_ctx, uint8_t brightness);

void st7789_letter (st7789_driver_t* st_ctx, unsigned char letter, uint16_t x, uint16_t y, uint16_t font_color, uint16_t background_color, const char* font_name);

void st7789_draw (st7789_driver_t* st_ctx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data);
void st7789_frame (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_fill_rounded (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_frame_rounded (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_add_custom_fonts (st7789_driver_t* st_ctx, st7789_font_t* custom_fonts_array_ptr, uint8_t amount);

void st7789_pixel (st7789_driver_t* st_ctx, uint16_t x, uint16_t y, uint16_t color);
void st7789_fill (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_line_vertical (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t h);
void st7789_line_horizontal (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w);

#endif // #ifndef __ST7789_DRIVER_H
#ifndef __ST7789_DRIVER_H
#define __ST7789_DRIVER_H

#include "stdint.h"
#include "st7789-colors.h"

#define ST7789_WIDTH 240
#define ST7789_HEIGHT 240

typedef void (*st7789_spi_w)  	(const void*, const uint8_t*, uint32_t);
typedef void (*st7789_pwm_rw)   (const void*, uint8_t*);
typedef void (*st7789_delay_us) (const void*, uint64_t);
typedef void (*st7789_gpio_put) (const void*);


typedef struct {
	const char* name;
	uint16_t width;
	uint16_t height;
	const uint8_t* data;
} st7789_font_t;

typedef struct {
	st7789_spi_w	spi_w;

	st7789_gpio_put	cs_set;
	st7789_gpio_put	cs_reset;

	st7789_gpio_put	dc_set;
	st7789_gpio_put	dc_reset;

	st7789_gpio_put	rst_set;
	st7789_gpio_put	rst_reset;

	st7789_pwm_rw  	set_brightness;
	st7789_pwm_rw  	get_brightness;

	st7789_delay_us delay_us;

	uint8_t rotation;
	uint16_t buffer[ST7789_WIDTH * ST7789_HEIGHT];

	st7789_font_t* default_font;

	st7789_font_t* custom_fonts;
	uint8_t sizeof_cfonts_array;

} st7789_driver_t;

#define ST7789_DEFAULT_ROTATION  	1
#define ST7789_DEFAULT_BRIGHTNESS 	100
#define ST7789_DEFAULT_COLOR  		ST7789_BLACK

void st7789_init(const void* ctx);
void st7789_set_rotation (const void* ctx, uint8_t m);
void st7789_fill_screen (const void* ctx, uint16_t color);

void st7789_letter (const void* ctx, unsigned char letter, uint16_t x, uint16_t y, uint16_t font_color, uint16_t background_color, const char* font_name);

void st7789_draw (const void* ctx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data);
void st7789_frame (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_fill_rounded (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_frame_rounded (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_add_custom_fonts (const void* ctx, st7789_font_t* custom_fonts_array_ptr, uint8_t amount);

void st7789_pixel (const void* ctx, uint16_t x, uint16_t y, uint16_t color);
void st7789_fill (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void st7789_line_vertical (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t h);
void st7789_line_horizontal (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w);

extern st7789_driver_t st7789_driver;

#endif // #ifndef __ST7789_DRIVER_H
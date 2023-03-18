#include "st7789-driver-private.h"
#include "st7789-driver.h"
#include "st7789-colors.h"
#include "st7789-font-default.h"

#include "stdbool.h"
#include "string.h"

const st7789_rotations_t st7789_rotations = {
	.rotation[0].x = X_SHIFT_R0,
	.rotation[0].y = Y_SHIFT_R0,

	.rotation[1].x = X_SHIFT_R1,
	.rotation[1].y = Y_SHIFT_R1,

	.rotation[2].x = X_SHIFT_R2,
	.rotation[2].y = Y_SHIFT_R2,

	.rotation[3].x = X_SHIFT_R3,
	.rotation[3].y = Y_SHIFT_R3,
};

void st7789_init(st7789_driver_t* st_ctx, uint16_t (*buffer)[ST7789_WIDTH * ST7789_HEIGHT])
{
	/* Default font init */
	st_ctx->fonts[0] = &jb_mono_bolditalic120x200;
	st_ctx->fonts_number = 1;

	/*  */
	st_ctx->buffer = buffer;

	/* Power on delay */
	st_ctx->public.delay_us(250*1000);

	/* Turn off the display during initialization */
  	st7789_off(st_ctx);
    st_ctx->public.delay_us(10*1000);

	/* Reset the display for 25ms */
	st_ctx->public.rst_reset();
    st_ctx->public.delay_us(25*1000);

    st_ctx->public.rst_set();
    st_ctx->public.delay_us(50*1000);

	/* Set color mode */
    st7789_set_rgb565(st_ctx);
	st_ctx->public.delay_us(25*1000);

	/* Set porch */
  	st7789_write8_command(st_ctx, ST7789_COMMAND_PORCTRL);
	uint8_t porctrl_data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
	st7789_write_data(st_ctx, porctrl_data, sizeof(porctrl_data));
	st_ctx->public.delay_us(25*1000);

	/* Set rotation to default value */
	st7789_set_rotation(st_ctx, ST7789_DEFAULT_ROTATION);
	st_ctx->public.delay_us(25*1000);
	
	/* Set internal LCD Voltage generator */
    st7789_write8_command(st_ctx, ST7789_COMMAND_GCTRL);
    st7789_write8_data(st_ctx, 0x35); 	// Default value
    st7789_write8_command(st_ctx, ST7789_COMMAND_VCOMS);
    st7789_write8_data(st_ctx, 0x19);	// 0.725v (default 0.75v for 0x20)
    st7789_write8_command(st_ctx, ST7789_COMMAND_LCMCTRL);
    st7789_write8_data (st_ctx, 0x2C);	// Default value
    st7789_write8_command (st_ctx, ST7789_COMMAND_VDVVRHEN);
    st7789_write8_data (st_ctx, 0x01);	// Default value
    st7789_write8_command (st_ctx, ST7789_COMMAND_VRHS);
    st7789_write8_data (st_ctx, 0x12); // +-4.45v (defalut +-4.1v for 0x0B)
    st7789_write8_command (st_ctx, ST7789_COMMAND_VDVSET);
    st7789_write8_data (st_ctx, 0x20);	// Default value
    st7789_write8_command (st_ctx, ST7789_COMMAND_FRCTR2);
    st7789_write8_data (st_ctx, 0x0F); // Default value (60HZ)
    st7789_write8_command (st_ctx, ST7789_COMMAND_PWCTRL1);
    st7789_write8_data (st_ctx, 0xA4);	// Default value
    st7789_write8_data (st_ctx, 0xA1);	// Default value
    st_ctx->public.delay_us(25*1000);

	/* Set positive voltage gamma control  */
	st7789_write8_command(st_ctx, ST7789_COMMAND_PVGAMCTRL);
	const uint8_t pvgamctrl_data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
	st7789_write_data(st_ctx, pvgamctrl_data, sizeof(pvgamctrl_data));
    st_ctx->public.delay_us(25*1000);

	/* Set negative voltage gamma control  */
    st7789_write8_command(st_ctx, ST7789_COMMAND_NVGAMCTRL);
	const uint8_t nvgactrl_data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
	st7789_write_data(st_ctx, nvgactrl_data, sizeof(nvgactrl_data));
	st_ctx->public.delay_us(25*1000);

	/* Inversion on */
    st7789_write8_command (st_ctx, ST7789_COMMAND_INVON);
	/* Out of sleep mode */
	st7789_write8_command (st_ctx, ST7789_COMMAND_SLPOUT);
	/* Normal dislay on */
  	st7789_write8_command (st_ctx, ST7789_COMMAND_NORON);

	/* Turn the display on */
	st7789_on(st_ctx);
	st_ctx->public.delay_us(50*1000);

	/* Draw default background */
	st7789_fill_screen(st_ctx, ST7789_DEFAULT_COLOR);
	//st_ctx->public.delay_us(10*1000); // ?????????????????????????????????
	
	/* Set default brightness level */
	st_ctx->brightness = ST7789_DEFAULT_BRIGHTNESS;
	st_ctx->public.set_brightness(&(st_ctx->brightness));
}

void st7789_add_custom_fonts (st7789_driver_t* st_ctx, st7789_font_t* custom_fonts_array_ptr, uint8_t amount) {
}

void st7789_set_rotation (st7789_driver_t* st_ctx, uint8_t m) {
	if (m >= 4) {
		return;
	}
	st_ctx->rotation = m;
	st7789_write8_command(st_ctx, ST7789_COMMAND_MADCTL);	// MADCTL
	switch (m) {
	case 0: st7789_write8_data(st_ctx, ST7789_MADCTL_DATA_R0); break;
	case 1: st7789_write8_data(st_ctx, ST7789_MADCTL_DATA_R1); break;
	case 2: st7789_write8_data(st_ctx, ST7789_MADCTL_DATA_R2); break;
	case 3: st7789_write8_data(st_ctx, ST7789_MADCTL_DATA_R3); break;
	}
}

void st7789_fill (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	if ((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT))
		return;
	if ((x + w - 1) >= ST7789_WIDTH)
		return;
	if ((y + h - 1) >= ST7789_HEIGHT)
		return;

	uint16_t i, j;
	for (i = 0; i < w; i++)
		for (j = 0; j < h; j++)
			(*st_ctx->buffer)[j*w + i] = color;

	st7789_draw(st_ctx, x, y, w, h, (*st_ctx->buffer));
}

void st7789_draw (st7789_driver_t* st_ctx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data) {
	if ((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT))
		return;
	if ((x + w - 1) >= ST7789_WIDTH)
		return;
	if ((y + h - 1) >= ST7789_HEIGHT)
		return;

	st7789_set_address_window(st_ctx, x, y, x + w - 1, y + h - 1);
	st7789_write_data(st_ctx, (uint8_t *)data, sizeof(uint16_t) * w * h);
}

void st7789_letter (st7789_driver_t* st_ctx, unsigned char letter, uint16_t x, uint16_t y, uint16_t font_color, uint16_t background_color, const char* font_name) {
	uint16_t i, j;
	st7789_font_t* font = NULL;
    
	font = st7789_get_font_by_name(st_ctx, font_name);

	uint32_t bytes_size = font->width * font->height / 8;

	for (j = 0; j < bytes_size; j++)
	{
		for (i = 0; i < 8; i++)
		{
            bool bit = !!((*(font->data + letter*bytes_size + j)) & (1 << i));
			if (bit == 1)
				(*st_ctx->buffer)[j*8 + i] = font_color;
			else
				(*st_ctx->buffer)[j*8 + i] = background_color;
		}
	}st_ctx->public.delay_us(2*1000);
	st7789_draw(st_ctx, x, y, font->width, font->height, (*st_ctx->buffer));
}

void st7789_frame (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	if ((x + w - 1) >= ST7789_WIDTH)
		return;
	if ((y + h - 1) >= ST7789_HEIGHT)
		return;

	st7789_line_horizontal (st_ctx, color, x, y, w);
	st7789_line_horizontal (st_ctx, color, x, y+h-1, w);

	st7789_line_vertical (st_ctx, color, x, y, h);
	st7789_line_vertical (st_ctx, color, x+w-1, y, h);
}

void st7789_pixel (st7789_driver_t* st_ctx, uint16_t x, uint16_t y, uint16_t color) {
	if ((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT))
		return;
	
	st7789_set_address_window(st_ctx, x, y, x, y);
	st7789_write_data(st_ctx, (uint8_t*) &color, sizeof(color));
}

void st7789_fill_rounded (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	if ((h % 2) != 0)
		return;

	uint16_t w_line = 0;
	uint16_t x_line = 1;

	for (uint16_t i = 0; i <= h/2; i++)
	{
		uint16_t x_len = 1;
		for (uint16_t j = 0; j < 3; j++)
		{
			if ((x_line - h/2)*(x_line - h/2) >= (h/2)*(h/2) - i*i)
			{
				x_line++;
				x_len++;
			}
			else
				break;
		}
		w_line = w - 2*x_line + 2*x_len;
		st7789_line_horizontal(st_ctx, color, x_line + x - x_len, y+h/2+i, w_line);
		if (i != 0)
			st7789_line_horizontal(st_ctx, color, x_line + x - x_len, y+h/2-i, w_line);
	}
}

void st7789_frame_rounded (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	if ((h % 2) != 0)
		return;

	uint16_t w_line = 0;
	uint16_t x_line = 1;

	for (uint16_t i = 0; i <= h/2; i++)
	{
		uint16_t x_len = 1;
		for (uint16_t j = 0; j < 3; j++)
		{
			if ((x_line - h/2)*(x_line - h/2) >= (h/2)*(h/2) - i*i)
			{
				x_line++;
				x_len++;
			}
			else
				break;
		}
		w_line = w - 2*x_line;
		
		st7789_line_horizontal(st_ctx, color, x_line + x-x_len, y+h/2+i, x_len);
		st7789_line_horizontal(st_ctx, color, x_line + x-x_len, y+h/2-i, x_len);

		st7789_line_horizontal(st_ctx, color, x_line + x + w_line - 1, y+h/2+i, x_len);
		st7789_line_horizontal(st_ctx, color, x_line + x + w_line - 1, y+h/2-i, x_len);

		if (i == h/2)
		{
			st7789_line_horizontal(st_ctx, color, x_line + x, y+h/2-i, w_line);
			st7789_line_horizontal(st_ctx, color, x_line + x, y+h/2+i, w_line);
		}
	}
}

void st7789_line_horizontal (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w) {
	st7789_fill (st_ctx, color, x, y, w, 1);
	return;
}

void st7789_line_vertical (st7789_driver_t* st_ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t h) {
	st7789_fill (st_ctx, color, x, y, 1, h);
	return;
}

void st7789_fill_screen (st7789_driver_t* st_ctx, uint16_t color) {
	st7789_fill(st_ctx, color, 0, 0, ST7789_WIDTH, ST7789_HEIGHT);
}

void st7789_set_brightness (st7789_driver_t* st_ctx, uint8_t brightness) {
	st_ctx->public.set_brightness(&brightness);
	st_ctx->brightness = brightness;
}

//===================================================================
//				Private functions
//===================================================================

void st7789_on(st7789_driver_t* st_ctx) {
	st7789_write8_command (st_ctx, ST7789_COMMAND_DISPON);	//	Main screen turned on	
}

void st7789_off(st7789_driver_t* st_ctx) {
	st7789_write8_command(st_ctx, ST7789_COMMAND_DISPOFF);	//	Main screen turned on
}

void st7789_set_rgb565(st7789_driver_t* st_ctx) {
	st7789_write8_command(st_ctx, ST7789_COMMAND_COLMOD);		//	Set color mode
    st7789_write8_data(st_ctx, ST7789_COLOR_MODE_16bit);
}

void st7789_write8_data(st7789_driver_t* st_ctx, uint8_t data) {
	st_ctx->public.cs_reset();
	st_ctx->public.dc_set();
	st_ctx->public.delay_us(1);

	st_ctx->public.spi_w(&data, 1);
	st_ctx->public.delay_us(1);

	st_ctx->public.cs_set();
    st_ctx->public.delay_us(2);
}

void st7789_write8_command(st7789_driver_t* st_ctx, uint8_t command) {
    st_ctx->public.cs_reset();
	st_ctx->public.dc_reset();
	st_ctx->public.delay_us(1);

    st_ctx->public.spi_w(&command, 1);
	st_ctx->public.delay_us(1);

    st_ctx->public.cs_set();
    st_ctx->public.delay_us(2);
}

void st7789_write_data(st7789_driver_t* st_ctx, const uint8_t *data, uint32_t size) {
    st_ctx->public.cs_reset();
	st_ctx->public.dc_set();
	st_ctx->public.delay_us(1);

	st_ctx->public.spi_w(data, size);
	st_ctx->public.delay_us(1);

	st_ctx->public.cs_set();
    st_ctx->public.delay_us(2);
}

void st7789_set_address_window (st7789_driver_t* st_ctx, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	if (st_ctx->rotation >= 4) {
		st_ctx->rotation = ST7789_DEFAULT_ROTATION;
	}
	int16_t x_shift = st7789_rotations.rotation[st_ctx->rotation].x;
	int16_t y_shift = st7789_rotations.rotation[st_ctx->rotation].y;
	uint16_t x_start = x0 + x_shift, x_end = x1 + x_shift;
	uint16_t y_start = y0 + y_shift, y_end = y1 + y_shift;
	
	/* Column Address set */
	st_ctx->public.delay_us(2);
	st7789_write8_command(st_ctx, ST7789_COMMAND_CASET); 
	{
		st_ctx->public.delay_us(2);
		uint8_t data[] = {(uint8_t)(x_start >> 8), (uint8_t)(x_start & 0xFF), (uint8_t)(x_end >> 8), (uint8_t)(x_end & 0xFF)};
		st7789_write_data(st_ctx, data, sizeof(data));
		st_ctx->public.delay_us(2);
	}

	/* Row Address set */
	st7789_write8_command(st_ctx, ST7789_COMMAND_RASET);
	{
		st_ctx->public.delay_us(2);
		uint8_t data[] = {(uint8_t)(y_start >> 8), (uint8_t)(y_start & 0xFF), (uint8_t)(y_end >> 8), (uint8_t)(y_end & 0xFF)};
		st7789_write_data(st_ctx, data, sizeof(data));
		st_ctx->public.delay_us(2);
	}
	/* Write to RAM */
	st7789_write8_command(st_ctx, ST7789_COMMAND_RAMWR);
}

st7789_font_t* st7789_get_font_by_name(st7789_driver_t* st_ctx, const char* font_name) {
	if (font_name == NULL) {
		return st_ctx->fonts[0];
	}
	if (strcmp(font_name, "default") == 0) {
		return st_ctx->fonts[0];
	}
	for (uint32_t i = 1; i < st_ctx->fonts_number; i++) {
		if (strcmp(font_name, st_ctx->fonts[i]->name) == 0) {
			return st_ctx->fonts[i];
		}
	}
	return st_ctx->fonts[0];
}

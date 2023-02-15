#include "st7789-driver-private.h"
#include "st7789-driver.h"
#include "st7789-colors.h"
#include "st7789-font.h"

#include "stdbool.h"

void st7789_init(const void* ctx)
{
	st7789_driver.delay_us(ctx, 250*1000);

  	st7789_off(ctx);
    st7789_driver.delay_us(ctx, 10*1000);

	st7789_driver.rst_reset(ctx);
    st7789_driver.delay_us(ctx, 25*1000);

    st7789_driver.rst_set(ctx);
    st7789_driver.delay_us(ctx, 50*1000);

    st7789_set_rgb565(ctx);
	st7789_driver.delay_us(ctx, 25*1000);
  	st7789_write8_command(ctx, 0xB2);				//	Porch control
	{
		uint8_t data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
		st7789_write_data(ctx, data, sizeof(data));
	}
	st7789_driver.delay_us(ctx, 25*1000);
	st7789_set_rotation(ctx, 0);	//	MADCTL (Display Rotation)
	st7789_driver.delay_us(ctx, 25*1000);
	
	/* Internal LCD Voltage generator settings */
    st7789_write8_command(ctx, 0XB7);				//	Gate Control
    st7789_write8_data(ctx, 0x35);			//	Default value
    st7789_write8_command(ctx, 0xBB);				//	VCOM setting
    st7789_write8_data(ctx, 0x19);			//	0.725v (default 0.75v for 0x20)
    st7789_write8_command(ctx, 0xC0);				//	LCMCTRL	
    st7789_write8_data (ctx, 0x2C);			//	Default value
    st7789_write8_command (ctx, 0xC2);				//	VDV and VRH command Enable
    st7789_write8_data (ctx, 0x01);			//	Default value
    st7789_write8_command (ctx, 0xC3);				//	VRH set
    st7789_write8_data (ctx, 0x12);			//	+-4.45v (defalut +-4.1v for 0x0B)
    st7789_write8_command (ctx, 0xC4);				//	VDV set
    st7789_write8_data (ctx, 0x20);			//	Default value
    st7789_write8_command (ctx, 0xC6);				//	Frame rate control in normal mode
    st7789_write8_data (ctx, 0x0F);			//	Default value (60HZ)
    st7789_write8_command (ctx, 0xD0);				//	Power control
    st7789_write8_data (ctx, 0xA4);			//	Default value
    st7789_write8_data (ctx, 0xA1);			//	Default value
	/**************** Division line ****************/
    st7789_driver.delay_us(ctx, 25*1000);
	st7789_write8_command(ctx, 0xE0);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
		st7789_write_data(ctx, data, sizeof(data));
	}
    st7789_driver.delay_us(ctx, 25*1000);
    st7789_write8_command(ctx, 0xE1);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
		st7789_write_data(ctx, data, sizeof(data));
	}
	st7789_driver.delay_us(ctx, 25*1000);
    st7789_write8_command (ctx, 0x21);		//	Inversion ON
	st7789_write8_command (ctx, 0x11);		//	Out of sleep mode
  	st7789_write8_command (ctx, 0x13);		//	Normal Display on
	st7789_on(ctx);

	st7789_driver.delay_us(ctx, 50*1000);
	st7789_fill_screen(ctx, ST7789_DEFAULT_COLOR);

	st7789_driver.delay_us(ctx, 200*1000); // ?????????????????????????????????
	uint8_t st_br = ST7789_DEFAULT_BRIGHTNESS;
	st7789_driver.set_brightness(ctx, &st_br);
}



void st7789_set_rotation (const void* ctx, uint8_t m) {
	st7789_write8_command(ctx, ST7789_MADCTL);	// MADCTL
	switch (m) {
	case 0:
		st7789_write8_data(ctx, ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
		break;
	case 1:
		st7789_write8_data(ctx, ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	case 2:
		st7789_write8_data(ctx, ST7789_MADCTL_RGB);
		break;
	case 3:
		st7789_write8_data(ctx, ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	default:
		break;
	}
}

void st7789_set_address_window (const void* ctx, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	uint16_t x_start = x0 + X_SHIFT, x_end = x1 + X_SHIFT;
	uint16_t y_start = y0 + Y_SHIFT, y_end = y1 + Y_SHIFT;
	
	/* Column Address set */
	st7789_driver.delay_us(ctx, 2);
	st7789_write8_command(ctx, ST7789_CASET); 
	{
		st7789_driver.delay_us(ctx, 2);
		uint8_t data[] = {(uint8_t)(x_start >> 8), (uint8_t)(x_start & 0xFF), (uint8_t)(x_end >> 8), (uint8_t)(x_end & 0xFF)};
		st7789_write_data(ctx, data, sizeof(data));
		st7789_driver.delay_us(ctx, 2);
	}

	/* Row Address set */
	st7789_write8_command(ctx, ST7789_RASET);
	{
		st7789_driver.delay_us(ctx, 2);
		uint8_t data[] = {(uint8_t)(y_start >> 8), (uint8_t)(y_start & 0xFF), (uint8_t)(y_end >> 8), (uint8_t)(y_end & 0xFF)};
		st7789_write_data(ctx, data, sizeof(data));
		st7789_driver.delay_us(ctx, 2);
	}
	/* Write to RAM */
	st7789_write8_command(ctx, ST7789_RAMWR);
}

void st7789_fill (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
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
			st7789_driver.buffer[j*w + i] = color;

	st7789_draw(ctx, x, y, w, h, st7789_driver.buffer);
}

void st7789_draw (const void* ctx, uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data) {
	if ((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT))
		return;
	if ((x + w - 1) >= ST7789_WIDTH)
		return;
	if ((y + h - 1) >= ST7789_HEIGHT)
		return;

	st7789_set_address_window(ctx, x, y, x + w - 1, y + h - 1);
	st7789_write_data(ctx, (uint8_t *)data, sizeof(uint16_t) * w * h);
}

void st7789_letter (const void* ctx, unsigned char letter, uint16_t x, uint16_t y, uint16_t font_color, uint16_t background_color) {
	uint16_t i, j;
    

	for (j = 0; j < JETBRAINSMONO_BOLD180_LSIZE; j++)
	{
		for (i = 0; i < 8; i++)
		{
            bool bit = !!((jetbrainsmono_bolditalic180_bmp [letter] [j]) & (1 << i));
			if (bit == 1)
				st7789_driver.buffer[j*8 + i] = font_color;
			else
				st7789_driver.buffer[j*8 + i] = background_color;
		}
	}st7789_driver.delay_us(ctx, 2*1000);
	st7789_draw(ctx, x, y, JETBRAINSMONO_BOLDITALIC180_WIDTH, JETBRAINSMONO_BOLDITALIC180_HEIGHT, st7789_driver.buffer);
}

void st7789_frame (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	if ((x + w - 1) >= ST7789_WIDTH)
		return;
	if ((y + h - 1) >= ST7789_HEIGHT)
		return;

	st7789_line_horizontal (ctx, color, x, y, w);
	st7789_line_horizontal (ctx, color, x, y+h-1, w);

	st7789_line_vertical (ctx, color, x, y, h);
	st7789_line_vertical (ctx, color, x+w-1, y, h);
}

void st7789_pixel (const void* ctx, uint16_t x, uint16_t y, uint16_t color) {
	if ((x >= ST7789_WIDTH) || (y >= ST7789_HEIGHT))
		return;
	
	st7789_set_address_window(ctx, x, y, x, y);
	st7789_write_data(ctx, (uint8_t*) &color, sizeof(color));
}

void st7789_fill_rounded (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
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
		st7789_line_horizontal(ctx, color, x_line + x - x_len, y+h/2+i, w_line);
		if (i != 0)
			st7789_line_horizontal(ctx, color, x_line + x - x_len, y+h/2-i, w_line);
	}
}

void st7789_frame_rounded (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
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
		
		st7789_line_horizontal(ctx, color, x_line + x-x_len, y+h/2+i, x_len);
		st7789_line_horizontal(ctx, color, x_line + x-x_len, y+h/2-i, x_len);

		st7789_line_horizontal(ctx, color, x_line + x + w_line - 1, y+h/2+i, x_len);
		st7789_line_horizontal(ctx, color, x_line + x + w_line - 1, y+h/2-i, x_len);

		if (i == h/2)
		{
			st7789_line_horizontal(ctx, color, x_line + x, y+h/2-i, w_line);
			st7789_line_horizontal(ctx, color, x_line + x, y+h/2+i, w_line);
		}
	}
}

void st7789_line_horizontal (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t w) {
	st7789_fill (ctx, color, x, y, w, 1);
	return;
}
void st7789_line_vertical (const void* ctx, uint16_t color, uint16_t x, uint16_t y, uint16_t h) {
	st7789_fill (ctx, color, x, y, 1, h);
	return;
}


void st7789_fill_screen (const void* ctx, uint16_t color) {
	st7789_fill(ctx, color, 0, 0, ST7789_WIDTH, ST7789_HEIGHT);
}

void st7789_on(const void* ctx) {
	st7789_write8_command (ctx, ST7789_DISPON);	//	Main screen turned on	
}

void st7789_off(const void* ctx) {
	st7789_write8_command(ctx, ST7789_DISPOFF);	//	Main screen turned on
}

void st7789_set_rgb565(const void* ctx) {
	st7789_write8_command(ctx, ST7789_COLMOD);		//	Set color mode
    st7789_write8_data(ctx, ST7789_COLOR_MODE_16bit);
}

void st7789_write8_data(const void* ctx, uint8_t data) {
	st7789_driver.cs_reset(ctx);
	st7789_driver.dc_set(ctx);
	st7789_driver.delay_us(ctx, 1);

	st7789_driver.spi_w(ctx, &data, 1);
	st7789_driver.delay_us(ctx, 1);

	st7789_driver.cs_set(ctx);
    st7789_driver.delay_us(ctx, 2);
}

void st7789_write8_command(const void* ctx, uint8_t command) {
    st7789_driver.cs_reset(ctx);
	st7789_driver.dc_reset(ctx);
	st7789_driver.delay_us(ctx, 1);

    st7789_driver.spi_w(ctx, &command, 1);
	st7789_driver.delay_us(ctx, 1);

    st7789_driver.cs_set(ctx);
    st7789_driver.delay_us(ctx, 2);
}

void st7789_write_data(const void* ctx, uint8_t *data, uint32_t size) {
    st7789_driver.cs_reset(ctx);
	st7789_driver.dc_set(ctx);
	st7789_driver.delay_us(ctx, 1);

	st7789_driver.spi_w(ctx, data, size);
	st7789_driver.delay_us(ctx, 1);

	st7789_driver.cs_set(ctx);
    st7789_driver.delay_us(ctx, 2);
}



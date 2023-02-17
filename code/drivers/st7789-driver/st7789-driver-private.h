#ifndef __ST7789_DRIVER_PRIVATE_H
#define __ST7789_DRIVER_PRIVATE_H

//===================================================================
//				Private header st7789-driver-private.h
//===================================================================

#include "st7789-driver.h"

/* Define shift depending on the size of the display */
#if ((ST7789_WIDTH == 240) && (ST7789_HEIGHT == 240))
	#define X_SHIFT_R0 0
	#define Y_SHIFT_R0 80

	#define X_SHIFT_R1 80
	#define Y_SHIFT_R1 0

	#define X_SHIFT_R2 0
	#define Y_SHIFT_R2 0

	#define X_SHIFT_R3 0
	#define Y_SHIFT_R3 0

#elif ((ST7789_WIDTH == 240) && (ST7789_HEIGHT == 280))
		#define X_SHIFT_R0 0
		#define Y_SHIFT_R0 20

		#define X_SHIFT_R1 20
		#define Y_SHIFT_R1 0

		#define X_SHIFT_R2 0
		#define Y_SHIFT_R2 20

		#define X_SHIFT_R3 0
		#define Y_SHIFT_R3 0

#else
	#error "st7789-driver: Uncompatible display size"
	#define X_SHIFT_R0 0
	#define Y_SHIFT_R0 0

	#define X_SHIFT_R1 0
	#define Y_SHIFT_R1 0

	#define X_SHIFT_R2 0
	#define Y_SHIFT_R2 0

	#define X_SHIFT_R3 0
	#define Y_SHIFT_R3 0
#endif

/* Commands */
#define ST7789_COMMAND_NOP 			0x00
#define ST7789_COMMAND_SWRESET 		0x01
#define ST7789_COMMAND_RDDID		0x04
#define ST7789_COMMAND_RDDST		0x09
#define ST7789_COMMAND_RDDPM		0x0A

#define ST7789_COMMAND_SLPIN 		0x10
#define ST7789_COMMAND_SLPOUT		0x11
#define ST7789_COMMAND_PTLON		0x12
#define ST7789_COMMAND_NORON		0x13

#define ST7789_COMMAND_INVOFF 		0X20
#define ST7789_COMMAND_INVON		0X21
#define ST7789_COMMAND_GAMSET		0X26
#define ST7789_COMMAND_DISPOFF		0X28
#define ST7789_COMMAND_DISPON		0X29
#define ST7789_COMMAND_CASET		0x2A
#define ST7789_COMMAND_RASET		0x2B
#define ST7789_COMMAND_RAMWR		0x2C
#define ST7789_COMMAND_RAMRD		0x2E

#define ST7789_COMMAND_PTLAR		0x30
#define ST7789_COMMAND_VSCRDEF		0x33
#define ST7789_COMMAND_TEOFF		0x34
#define ST7789_COMMAND_TEON			0x35
#define ST7789_COMMAND_MADCTL		0x36
#define ST7789_COMMAND_VSCRSADD		0x37
#define ST7789_COMMAND_IDMOFF		0x38
#define ST7789_COMMAND_IDMON		0x39
#define ST7789_COMMAND_COLMOD		0x3A
#define ST7789_COMMAND_RAMWRC		0x3C
#define ST7789_COMMAND_RAMRDC		0x3E

#define ST7789_COMMAND_RAMCTRL		0xB0
#define ST7789_COMMAND_RGBCTRL		0xB1
#define ST7789_COMMAND_PORCTRL		0xB2
#define ST7789_COMMAND_GCTRL		0xB7
#define ST7789_COMMAND_GTADJ		0xB8
#define ST7789_COMMAND_DGMEN		0xBA
#define ST7789_COMMAND_VCOMS		0xBB

#define ST7789_COMMAND_LCMCTRL		0xC0
#define ST7789_COMMAND_IDSET		0xC1
#define ST7789_COMMAND_VDVVRHEN		0xC2
#define ST7789_COMMAND_VRHS			0xC3
#define ST7789_COMMAND_VDVSET		0xC4
#define ST7789_COMMAND_VCMOFSET		0xC5
#define ST7789_COMMAND_FRCTR2		0xC6

#define ST7789_COMMAND_PWCTRL1		0xD0

#define ST7789_COMMAND_PVGAMCTRL	0xE0
#define ST7789_COMMAND_NVGAMCTRL	0xE1

/* Display orientation register */
/* Page Address Order ('0': Top to Bottom, '1': the opposite) */
#define ST7789_MADCTL_MY  0x80  
/* Column Address Order ('0': Left to Right, '1': the opposite) */
#define ST7789_MADCTL_MX  0x40  
/* Page/Column Order ('0' = Normal Mode, '1' = Reverse Mode) */
#define ST7789_MADCTL_MV  0x20  
/* Line Address Order ('0' = LCD Refresh Top to Bottom, '1' = the opposite) */
#define ST7789_MADCTL_ML  0x10
/* RGB/BGR Order ('0' = RGB, '1' = BGR) */
#define ST7789_MADCTL_RGB 0x00

#define ST7789_MADCTL_DATA_R0 (ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB)
#define ST7789_MADCTL_DATA_R1 (ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB)
#define ST7789_MADCTL_DATA_R2 (ST7789_MADCTL_RGB)
#define ST7789_MADCTL_DATA_R3 (ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB)

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

/* Display color mode */
#define ST7789_COLOR_MODE_16bit 0x55    //  RGB565 (16bit)
#define ST7789_COLOR_MODE_18bit 0x66    //  RGB666 (18bit)

/* Private functions */
void st7789_on(st7789_driver_t* st_ctx);
void st7789_off(st7789_driver_t* st_ctx);
void st7789_set_rgb565(st7789_driver_t* st_ctx);
st7789_font_t* st7789_get_font_by_name(st7789_driver_t* st_ctx, const char* font_name);
void st7789_set_address_window (st7789_driver_t* st_ctx, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

void st7789_write8_data(st7789_driver_t* st_ctx, uint8_t data);
void st7789_write8_command(st7789_driver_t* st_ctx, uint8_t command);
void st7789_write_data(st7789_driver_t* st_ctx, const uint8_t *data, uint32_t size);

typedef struct {
	int16_t x;
	int16_t y;
} st7789_rotation_offsets_t;
typedef struct {
	st7789_rotation_offsets_t rotation[4];
} st7789_rotations_t;


#endif // #ifndef __ST7789_DRIVER_PRIVATE_H
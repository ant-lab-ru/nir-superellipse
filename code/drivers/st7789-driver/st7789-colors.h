#ifndef __ST7789_COLORS_H
#define __ST7789_COLORS_H

// Color is a 16bit word in RGB565 format
// But!
// Endianness big-endian
// So, bits are: G2 G1 G0 B4 B3 B2 B1 B0 R4 R3 R2 R1 R0 G5 G4 G3

// Simple colors

#define ST7789_WHITE       0xFFFF
#define ST7789_BLACK       0x0000
#define ST7789_GREEN       0xE007
#define ST7789_BLUE        0x1F00
#define ST7789_RED         0x00F8

// Beautiful colors

#define ST7789_MAGENTA     0x1FF8

// Grey colors



#define ST7789_GREEN_R165_G255_B165 0xF4A7
#define ST7789_GREY_R200_G200_B200  0x59CE
#define ST7789_GREY_R100_G100_B100  0x2C63
#define ST7789_GREY_R050_G050_B050  0x8631

#endif // #ifndef __ST7789_COLORS_H
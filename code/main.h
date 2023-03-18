#ifndef __MAIN_H
#define __MAIN_H

#include "stdint.h"

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct HSV {
    uint16_t h; // from 0 to 360
    uint8_t s;
    uint8_t v;
};

enum States {
    STATE_MONOCHROME_RGB = 0,
    STATE_MONOCHROME_HSV,
    STATE_BLINK,
    STATE_SECRET,
};

enum Blink_modes {
    BLINK_MODE_WAVE = 0,
    BLIND_MODE_END,
};

struct Superellipse {
    enum States state;

    struct RGB rgb_color;
    struct HSV hsv_color;
    enum Blink_modes blink_mode;
};

extern struct Superellipse superellipse;

#endif // #ifndef __MAIN_H
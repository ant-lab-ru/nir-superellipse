#ifndef __MAIN_H
#define __MAIN_H

#include "stdint.h"

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

enum {
    STATE_MONOCHROME = 0,
    STATE_BLINK,
};

enum {
    BLINK_MODE_WAVE = 0,
};

struct Superellipse {
    uint8_t state;

    struct Color color;

    uint8_t blink_mode;
};

extern struct Superellipse superellipse;

#endif // #ifndef __MAIN_H
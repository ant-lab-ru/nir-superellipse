#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "hardware/spi.h"

typedef int (*spi_wr) (spi_inst_t*, const uint8_t*, size_t);

typedef struct {
    void* spix;
    uint32_t    bitrate;
    spi_wr      write;
} spi_ctx_t;


extern spi_ctx_t display_spi_ctx;

void init_hardware();

#endif // #ifndef __HARDWARE_H
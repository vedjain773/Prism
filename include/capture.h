#ifndef CAPTURE_H
#define CAPTURE_H

#include "miniaudio.h"

void data_callback(ma_device* pDevice,
                   void* pOutput,
                   const void* pInput,
                   ma_uint32 frameCount);

int init_ma();
void dinit_ma();

void get_latest_samples(float* dest, size_t count);

#endif

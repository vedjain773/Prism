#include "capture.h"
#include <stdio.h>
#include <math.h>
#include <stdatomic.h>
#include <assert.h>

#define HISTORY 32768

static float buffer[HISTORY];
static atomic_size_t wpos = 0;

static ma_device device;
static ma_context context;

void data_callback(ma_device* pDevice,
                   void* pOutput,
                   const void* pInput,
                   ma_uint32 frameCount)
{
    const float* samples = pInput;

    for (ma_uint32 i = 0; i < frameCount; i++) {
        float mono = samples[i];
        
        size_t pos = atomic_load(&wpos);
        buffer[pos] = mono;

        atomic_store(&wpos, (pos + 1) & (HISTORY - 1));
    } 
    
    (void)pDevice;
    (void)pOutput;
}

void get_latest_samples(float* dst, size_t count)
{
    size_t pos = atomic_load(&wpos);

    for (size_t i = 0; i < count; i++) {
        size_t idx =
            (pos + HISTORY - count + i) % HISTORY;

        dst[i] = buffer[idx];
    }
}

int init_ma()
{
    ma_result result;
    ma_device_info* pPlaybackDeviceInfos;
    ma_uint32 playbackDeviceCount;
    ma_device_info* pCaptureDeviceInfos;
    ma_uint32 captureDeviceCount;
    ma_uint32 iDevice;

    if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
        printf("Failed to initialize context.\n");
        return -2;
    }

    result = ma_context_get_devices(
            &context,
            &pPlaybackDeviceInfos,
            &playbackDeviceCount,
            &pCaptureDeviceInfos,
            &captureDeviceCount);
    
    if (result != MA_SUCCESS) {
        printf("Failed to retrieve device information.\n");
        return -3;
    }

    ma_device_config config = ma_device_config_init(ma_device_type_capture);
    config.capture.pDeviceID = &pCaptureDeviceInfos[0].id;
    config.capture.format = ma_format_f32;
    config.capture.channels = 1;
    config.sampleRate = 44100;
    config.dataCallback = data_callback;

    assert(config.capture.channels == 1);
        
    result = ma_device_init(&context, &config, &device);
    if (result != MA_SUCCESS) {
        printf("Init failed: %d\n", result);
        return -1;
    }

    result = ma_device_start(&device);
    if (result != MA_SUCCESS) {
        printf("Start failed: %d\n", result);
        ma_device_uninit(&device);
        return -1;
    }
    
    return 0;
}

void dinit_ma() {
    ma_device_uninit(&device);
    ma_context_uninit(&context);

    return;
}

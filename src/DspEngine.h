#ifndef TURBTROLL_DSPENGINE_H
#define TURBTROLL_DSPENGINE_H

#include "AdcHandler.h"

#include "Config.h"

#include "microsmooth.h"

class DspEngine {
    public:
        DspEngine(float _fs_hz);
        void RegisterCallback(AdcHandler *_callback);
        virtual float GetFrequency();
        void RegisterFreqPtr(float* _freqPtr);
    protected:
        float last_result; 
        unsigned long internal_count;
        float sample_interval_s;
        AdcHandler *callback;
        int* buff =  (int*)malloc(FFT_BUFFER_SZ * sizeof(int));
        uint16_t *history = ms_init(SMA);
        float* freq_ptr; 
};

#endif
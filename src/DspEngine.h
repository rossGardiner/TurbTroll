#ifndef TURBTROLL_DSPENGINE_H
#define TURBTROLL_DSPENGINE_H

#include "AdcHandler.h"
#include <CircularBuffer.h>
#define BUFFER_SZ 300

class DspEngine {
    public:
        DspEngine(float _fs_hz);
        void RegisterCallback(AdcHandler *_callback);
        float GetFrequency();

    protected:
        //float GetDCOffset();
        float fs_hz;
        AdcHandler *callback;
        CircularBuffer<float, BUFFER_SZ> buffer;
};

#endif
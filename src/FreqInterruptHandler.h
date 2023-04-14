#ifndef TURBTROLL_FREQINTERRUPTHANDLER_H
#define TURBTROLL_FREQINTERRUPTHANDLER_H

#include <Arduino.h>

#include "Config.h"

#include "microsmooth.h"


class FreqInterruptHandler{
    public:
        static volatile unsigned int pulse_count;
        FreqInterruptHandler();
        void Begin();
        float GetFreq(int delay_ms);
        void RegisterFreqPtr(float* _freqPtr);

        //a VERY lean interrupt routine - gives best performance
        static void interrupt_routine(){
            pulse_count++;
            #if DEBUG == 1
            //digitalWriteFast(LED_BUILTIN, pulse_count%2);
            #endif
        }

    protected:
        float* freq_ptr; 
        uint16_t *history = ms_init(SMA);

    
};


#endif
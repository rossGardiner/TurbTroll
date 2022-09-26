#ifndef TURBTROLL_ADC_HANDLER_H
#define TURBTROLL_ADC_HANDLER_H

#include <Arduino.h>

class AdcHandler {
    public:
        AdcHandler();
        AdcHandler(int _adcPin);
        float GetSample();
    
    private:
        int midpoint;
        int adcPin;
        int resolution;
        const float logic_level_volts = 5.0;
};

#endif
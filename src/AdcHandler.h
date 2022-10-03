#ifndef TURBTROLL_ADC_HANDLER_H
#define TURBTROLL_ADC_HANDLER_H

#include <Arduino.h>

class AdcHandler {
    public:
        AdcHandler(int _adcPin);
        AdcHandler();
        
        virtual float GetSample();
    
    private:
        int midpoint;
        int adcPin;
        int nr_steps;
        const float logic_level_volts = 5.0;
};

#endif
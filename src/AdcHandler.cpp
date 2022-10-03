#include "AdcHandler.h"

#include <math.h>

#include "DebugMonitor.h"

AdcHandler::AdcHandler(): AdcHandler(A0) {}

AdcHandler::AdcHandler(int _adcPin){
    adcPin = _adcPin;
    pinMode(adcPin, INPUT);
    debug("Pin: %d\n", adcPin);
    nr_steps = pow(2, 10);
}

float AdcHandler::GetSample(){
    float valueAtAdc = float(analogRead(adcPin)); //value between 0--1023 
    debug("Value at adc: %f\n", valueAtAdc);
    float value_volts = (valueAtAdc / nr_steps) * logic_level_volts;
    return value_volts;
}
    
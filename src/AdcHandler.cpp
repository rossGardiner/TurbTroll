#include "AdcHandler.h"

#include <math.h>

#include "DebugMonitor.h"

AdcHandler::AdcHandler(): AdcHandler(A0) {}

AdcHandler::AdcHandler(int _adcPin){
    adcPin = _adcPin;
    pinMode(adcPin, INPUT);
    nr_steps = pow(2, 10);
}

int AdcHandler::GetSample(){
    //float valueAtAdc = float(analogRead(adcPin)); //value between 0--1023 
    //debug("m0: %d\n", millis());
    //float value_volts = (valueAtAdc / nr_steps) * logic_level_volts;
    return analogRead(adcPin);
}
    
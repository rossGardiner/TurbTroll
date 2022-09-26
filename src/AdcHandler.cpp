#include "AdcHandler.h"

#include <math.h>

AdcHandler::AdcHandler(){
    AdcHandler(A0);
}

AdcHandler::AdcHandler(int _adcPin){
    adcPin = _adcPin;
    resolution = pow(2, 10);
}

float AdcHandler::GetSample(){
    int valueAtAdc = analogRead(adcPin); //value between 0--1023 
    float value_volts = (valueAtAdc / resolution) * logic_level_volts;
    return value_volts;
}
    
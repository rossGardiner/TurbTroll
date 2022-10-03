#include "PwmHandler.h"

PWMHander::PWMHander(int pwmPin=12){
    pinNo = pwmPin;
    pinMode(pinNo, OUTPUT);
}

void PWMHander::RegisterCallback(DecisionMaker* _callback){
    callback = _callback;
}

float PWMHander::UpdateDutyCycle(){
    float adjustment = callback->GetPWMAdjustment();
    dutyCycle = constrain(dutyCycle + adjustment, 0.0, 1.0);
    int asInt = dutyCycle * 255;
    analogWrite(pinNo, asInt); 
    return dutyCycle;
}
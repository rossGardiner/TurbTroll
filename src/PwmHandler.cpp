#include "PwmHandler.h"

PWMHandler::PWMHandler(int pwmPin){
    pinNo = pwmPin;
    pinMode(pinNo, OUTPUT);
    analogWriteFreq(PWM_FREQ);
}

void PWMHandler::RegisterCallback(DecisionMaker* _callback){
    callback = _callback;
}

void PWMHandler::RegisterDutyPtr(float* _dutyPtr){
    dutyPtr = _dutyPtr;
}

float PWMHandler::UpdateDutyCycle(){
    float adjustment = callback->GetPWMAdjustment();
    dutyCycle = constrain(dutyCycle + adjustment, 0.0, 1.0);
    *dutyPtr = dutyCycle;
    int asInt = dutyCycle * 255;
    analogWrite(pinNo, asInt); 
    return dutyCycle;
}
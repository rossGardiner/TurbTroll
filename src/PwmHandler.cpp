#include "DebugMonitor.h"
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
    int dutyCycle = callback->GetPWM();
    float dutyPercent = dutyCycle/255.0 * 100.0;
    *dutyPtr = dutyPercent;
    return dutyCycle;
}


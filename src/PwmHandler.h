#ifndef TURBTROLL_PWMHANDLER_H
#define TURBTROLL_PWMHANDLER_H
#include <Arduino.h>
#include "DecisionMaker.h"


class PWMHandler {
    public:
        PWMHandler(int pwmPin);
        void RegisterCallback(DecisionMaker* _callback);
        void RegisterDutyPtr(float* _dutyPtr);
        float UpdateDutyCycle();
     


    protected:
        int channelNr;
        DecisionMaker* callback;
        float dutyCycle = 0.0f;
        int pinNo;
        float* dutyPtr;
        int period_ms = 1000 / PWM_FREQ;
};

#endif
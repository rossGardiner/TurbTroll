#ifndef TURBTROLL_PWMHANDLER_H
#define TURBTROLL_PWMHANDLER_H
#include <Arduino.h>

#include "DecisionMaker.h"

class PWMHandler {
    public:
        PWMHandler(int pwmPin=12);
        void RegisterCallback(DecisionMaker* _callback);
        void RegisterDutyPtr(float* _dutyPtr);
        float UpdateDutyCycle();


    protected:
        DecisionMaker* callback;
        float dutyCycle = 0.0f;
        int pinNo = 12;
        float* dutyPtr;
};

#endif
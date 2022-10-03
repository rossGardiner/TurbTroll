#ifndef TURBTROLL_PWMHANDLER_H
#define TURBTROLL_PWMHANDLER_H
#include <Arduino.h>

#include "DecisionMaker.h"

class PWMHander {
    public:
        PWMHander(int pwmPin=12);
        void RegisterCallback(DecisionMaker* _callback);
        float UpdateDutyCycle();

    protected:
        int pinNo = 12;
        DecisionMaker* callback;
        float dutyCycle = 0.0f;
};

#endif
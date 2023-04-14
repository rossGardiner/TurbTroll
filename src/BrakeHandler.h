#ifndef TURBTROLL_BRAKEHANDLER_H
#define TURBTROLL_BRAKEHANDLER_H

#include <Arduino.h>

#include "Config.h"


class BrakeHandler{
    public:
        BrakeHandler(int brakePin);
        void Brake();
        void Release();
        void BrakeHold(int hold_ms);
    protected:
        int brakePin;
};


#endif
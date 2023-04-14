#ifndef TURBTROLL_DECISIONMAKER_H
#define TURBTROLL_DECISIONMAKER_H

#include "FreqInterruptHandler.h"
#include "BrakeHandler.h"

enum class DecisionState {
	FREESPIN,
	MODULATING,
	BRAKE
};

class DecisionMaker {
    public:
        DecisionMaker(int _delay_ms);
        void RegisterFrequencyCallback(FreqInterruptHandler* _callback);
        void RegisterBrakeCallback(BrakeHandler* _callback);
        void RegisterStatePtr(DecisionState* _state);
        virtual long GetPWM();
        float rpmToHz(float rpm);
        float hzToRpm(float hz);
        DecisionState speedStatus(float freq);
        float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
        float fullModulationTargetHz;
        float minTargetHz;
        float maxTargetHz;


    protected:
        FreqInterruptHandler* frequencyCallback;
        BrakeHandler* brakeCallback;
        
        float stepSize;
        int nrPoles;
        int freqDivision;
        int delay_ms = 500;
        DecisionState internalState = DecisionState::FREESPIN;
        DecisionState* statePtr;
};

#endif
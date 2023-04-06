#ifndef TURBTROLL_DECISIONMAKER_H
#define TURBTROLL_DECISIONMAKER_H

#include "DspEngine.h"

enum class DecisionState {
	FREESPIN,
	SPEED_UP,
	SPEED_DOWN
};

class DecisionMaker {
    public:
        DecisionMaker(float _stepSize=0.01);
        void RegisterCallback(DspEngine* _callback);
        void RegisterStatePtr(DecisionState* _state);
        virtual float GetPWMAdjustment();
        float rpmToHz(float rpm);
        DecisionState speedStatus(float freq);


    protected:
        DspEngine* dspCallback;
        float targetHz;
        float minTargetHz;
        float maxTargetHz;
        float stepSize;
        int nrPoles;
        int freqDivision;
        DecisionState internalState = DecisionState::FREESPIN;
        DecisionState* statePtr;
};

#endif
#ifndef TURBTROLL_DECISIONMAKER_H
#define TURBTROLL_DECISIONMAKER_H

#include "DspEngine.h"

enum class DecisionState {
	INITIAL_RAMP,
	RAMP_DOWN,
	RAMP_UP
};

class DecisionMaker {
    public:
        DecisionMaker(int _nrPoles, float _stationaryBoundaryRpm, float _minRpm, float _maxRpm, float _stepSize);
        void RegisterCallback(DspEngine* _callback);
        virtual float GetPWMAdjustment();
        protected:
        float doInitialRamp();
        float doRampDowm(float rpm);
        float doRampUp(float rpm);

    protected:
        DspEngine* dspCallback;
        float minTargetRpm = 0.0f;
        float maxTargetRpm = 0.0f;
        float stationaryBoundaryRpm = 0.0f;
        float stepSize = 0.0f;
        int nrPoles = 0;
        DecisionState internalState = DecisionState::INITIAL_RAMP;
};

#endif
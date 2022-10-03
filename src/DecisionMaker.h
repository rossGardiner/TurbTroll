#ifndef TURBTROLL_DECISIONMAKER_H
#define TURBTROLL_DECISIONMAKER_H

#include "DspEngine.h"

enum class DecisionState {
	IDLE,
	INITIAL_RAMP,
	RAMP_DOWN,
	RAMP_UP
};

class DecisionMaker {
    public:
        DecisionMaker(int _nrPoles, float _stationaryBoundaryRpm, float _minRpm, float _maxRpm, float _stepSize);
        void RegisterCallback(DspEngine* _callback);
        float GetPWMAdjustment();
    protected:
        DspEngine* dspCallback;
        float minTargetRpm = 0.0f;
        float maxTargetRpm = 0.0f;
        float stationaryBoundaryRpm = 0.0f;
        float stepSize = 0.0f;
        int nrPoles = 0;
        DecisionState internalState = DecisionState::IDLE;
};

#endif
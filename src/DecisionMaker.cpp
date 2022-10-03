#include "DecisionMaker.h"


DecisionMaker::DecisionMaker(int _nrPoles, float _stationaryBoundaryRpm, float _minTargetRpm, float _maxTargetRpm, float _stepSize){
    nrPoles = _nrPoles;
    stationaryBoundaryRpm = _stationaryBoundaryRpm;
    minTargetRpm = _minTargetRpm; maxTargetRpm = _maxTargetRpm;
    stepSize = _stepSize;
}

void DecisionMaker::RegisterCallback(DspEngine* _callback){
    dspCallback = _callback;
}

float DecisionMaker::doInitialRamp(){
    //turn the load off, -1.0 (-100%) is the signal for this
    return -1.0f;
}

float DecisionMaker::doRampUp(float rpm){
    //decrease duty cycle -- try to reduce turbine speed
    return -1.0 * stepSize;
}

float DecisionMaker::doRampDowm(float rpm){
    //increase duty cycle -- try to reduce turbine speed
    return 1.0 * stepSize;
}

float DecisionMaker::GetPWMAdjustment(){
    /*
    Starting up from low speed, the controller would not put anything into the heater until the upper target speed is achieved
    then slowly increase the load until the lower target speed. 
    Lower than the lower target speed it backs off the load, 
    higher than the upper target speed it increases the load.
    */

    //current speed - hz, times seconds in a minate
    float currentRpm = dspCallback->GetFrequency() * 60.0 * (2.0 / nrPoles);
    if(internalState == DecisionState::INITIAL_RAMP) {
        if(currentRpm >= maxTargetRpm){
            internalState = DecisionState::RAMP_DOWN;
        }
        else{
            return doInitialRamp();
        }
    }
    if (internalState == DecisionState::RAMP_DOWN){
        if (currentRpm >= minTargetRpm){
            return doRampDowm(currentRpm);
        }
        else if (currentRpm <= stationaryBoundaryRpm){
            internalState = DecisionState::INITIAL_RAMP;
            return doInitialRamp();
        }
        else {
            internalState = DecisionState::RAMP_UP;
            return doRampUp(currentRpm);
        }
    }
      
    if (internalState == DecisionState::RAMP_UP){
        if (currentRpm <= stationaryBoundaryRpm){
            internalState = DecisionState::INITIAL_RAMP;
            return doInitialRamp();
        }
        else if (currentRpm <= maxTargetRpm){
            return doRampUp(currentRpm);
        }
        else{
            internalState = DecisionState::RAMP_DOWN;
            return doRampDowm(currentRpm);
        }
    }
    //do nothing, default case
    return 0.0f;
}
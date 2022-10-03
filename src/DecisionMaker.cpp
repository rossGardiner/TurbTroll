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

float DecisionMaker::GetPWMAdjustment(){
    /*
    Starting up from low speed, the controller would not put anything into the heater until the upper target speed is achieved
    then slowly increase the load until the lower target speed. 
    Lower than the lower target speed it backs off the load, 
    higher than the upper target speed it increases the load.
    */

    //current speed - hz, times seconds in a minate
    float currentRpm = dspCallback->GetFrequency() * 60.0 * (2.0 / nrPoles);
    switch(internalState) {
        case DecisionState::IDLE:
            internalState = DecisionState::INITIAL_RAMP;
        case DecisionState::INITIAL_RAMP:
            if(currentRpm >= maxTargetRpm){
                internalState = DecisionState::RAMP_DOWN;
            }
            else{
                //turn the load off, -1.0 (-100%) is the signal for this
                return -1.0f;
            }
        case DecisionState::RAMP_DOWN:
            if (currentRpm >= minTargetRpm){
                //increase duty cycle -- try to reduce turbine speed
                return 1.0 * stepSize;
            }
            else {
                internalState = DecisionState::RAMP_UP;
            }
        case DecisionState::RAMP_UP:
            if (currentRpm <= maxTargetRpm){
                //decrease duty cycle -- try to increase turbine speed
                return -1.0 * stepSize;
            }
            else{
                internalState = DecisionState::RAMP_DOWN;
            }
        default:
            break;
}
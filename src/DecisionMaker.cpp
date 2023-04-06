#include "DecisionMaker.h"
#include "DebugMonitor.h"
#include "Config.h"


DecisionMaker::DecisionMaker(float _stepSize){
    nrPoles = NR_POLES;
    freqDivision = FREQ_DIVISION;
    minTargetHz = rpmToHz(MIN_RPM); 
    maxTargetHz = rpmToHz(MAX_RPM);
    targetHz = rpmToHz(TARGET_RPM);
    stepSize = _stepSize;

}

void DecisionMaker::RegisterCallback(DspEngine*  _callback){
    dspCallback = _callback;
}

void DecisionMaker::RegisterStatePtr(DecisionState* _state){
    statePtr = _state;
}


DecisionState DecisionMaker::speedStatus(float freq){
    if (freq < minTargetHz || freq >= maxTargetHz){
        return DecisionState::FREESPIN;
    }
    if (freq < targetHz){
        return DecisionState::SPEED_UP;
    }
    else{
        return DecisionState::SPEED_DOWN;
    }
}

float DecisionMaker::rpmToHz(float rpm){
    return rpm * (1.0/60) * (nrPoles/2) * freqDivision;
}

float DecisionMaker::GetPWMAdjustment(){
    float f = dspCallback->GetFrequency();
    internalState = speedStatus(f);
    if (internalState == DecisionState::SPEED_UP){
        return -stepSize;
    }
    else if (internalState == DecisionState::SPEED_DOWN){
        return stepSize;
    }
    else{
        return - __FLT_MAX__;
    }
}
//float DecisionMaker::GetPWMAdjustment(){
       
//     /*
//     Starting up from low speed, the controller would not put anything into the heater until the upper target speed is achieved
//     then slowly increase the load until the lower target speed. 
//     Lower than the lower target speed it backs off the load, 
//     higher than the upper target speed it increases the load.
//     */

//     //current speed - hz, times seconds in a minate
//     float freq = dspCallback->GetFrequency();
//     if(internalState == DecisionState::INITIAL_RAMP) {
//         if(freq >= maxTargetHz){
//             internalState = DecisionState::RAMP_DOWN;
//         }
//         else{
//             return doInitialRamp();
//         }
//     }
//     if (internalState == DecisionState::RAMP_DOWN){
//         if (freq >= minTargetHz){
//             return doRampDowm(freq);
//         }
//         else if (freq <= stationaryBoundaryHz){
//             internalState = DecisionState::INITIAL_RAMP;
//             return doInitialRamp();
//         }
//         else {
//             internalState = DecisionState::RAMP_UP;
//             return doRampUp(freq);
//         }
//     }
      
//     if (internalState == DecisionState::RAMP_UP){
//         if (freq <= stationaryBoundaryHz){
//             internalState = DecisionState::INITIAL_RAMP;
//             return doInitialRamp();
//         }
//         else if (freq <= maxTargetHz){
//             return doRampUp(freq);
//         }
//         else{
//             internalState = DecisionState::RAMP_DOWN;
//             return doRampDowm(freq);
//         }
//     }
//     //do nothing, default case
//    return 0.0f;
//}
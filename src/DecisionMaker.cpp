#include "DecisionMaker.h"
#include "DebugMonitor.h"

#include "Config.h"
#include "DebugMonitor.h"

DecisionMaker::DecisionMaker(int _delay_ms){
    nrPoles = NR_POLES;
    freqDivision = FREQ_DIVISION;
    minTargetHz = rpmToHz(MIN_RPM); 
    fullModulationTargetHz = rpmToHz(FULL_MOD_RPM);
    maxTargetHz = rpmToHz(MAX_RPM);
    delay_ms = _delay_ms;
} 

void DecisionMaker::RegisterFrequencyCallback(FreqInterruptHandler*  _callback){
    frequencyCallback = _callback;
}

void DecisionMaker::RegisterBrakeCallback(BrakeHandler* _callback){
    brakeCallback = _callback;
}


void DecisionMaker::RegisterStatePtr(DecisionState* _state){
    statePtr = _state;
}


DecisionState DecisionMaker::speedStatus(float freq){
    if (freq < minTargetHz){
        return DecisionState::FREESPIN;
    }
    else if (freq < maxTargetHz){
        return DecisionState::MODULATING;
    }
    else{
        return DecisionState::BRAKE;
    }
}

float DecisionMaker::rpmToHz(float rpm){
    return rpm * (1.0/60) * (nrPoles);
}
float DecisionMaker::hzToRpm(float hz){
    return 60.0 * hz / (nrPoles);
}

float DecisionMaker::mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

long DecisionMaker::GetPWM(){
    float frequency = frequencyCallback->GetFreq(delay_ms);
    internalState = speedStatus(frequency);
    *statePtr = internalState;
    if (internalState == DecisionState::FREESPIN){
        return 0;
    }
    else if (internalState == DecisionState::MODULATING){
        return map(
            constrain(frequency, 0.0, fullModulationTargetHz),
            minTargetHz, 
            fullModulationTargetHz, 
            0, 255
        );
    }
    else 
        return 255;
}

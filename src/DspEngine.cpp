#include "DspEngine.h"
#include <Arduino.h>
#include <string.h>

#include "DebugMonitor.h"


DspEngine::DspEngine(float _fs_hz){
    fs_hz = _fs_hz;
};

void DspEngine::RegisterCallback(AdcHandler *_callback){
    callback = _callback;
}

float DspEngine::GetDCOffset(){
    //it may make more sense to just return 2.5Volts, not sure about the sensor drift yet!
    //dc offset computed as the average in the buffer
    int sz = buffer.size(); 
    float total = 0.0f;
    for (int i = 0; i < sz - 1; i++) {
        total += buffer[i];
    }
    return total / (1.0 * sz);
}

float DspEngine::GetFrequency(){
    
    float adc_volts = callback->GetSample();
    //debug("Adc volts: %f\n", adc_volts);
    buffer.push(adc_volts);
    //debug("Buffer size: %d\n", buffer.size());

    if(buffer.size() < 3) return -1.0;
    float zeroPoint = GetDCOffset();
    //debug("Zero point: %f\n", zeroPoint);
    float lastValue       = buffer[buffer.size() - 1];
    bool referenceSign = lastValue > zeroPoint;
    int signChange = 0;
    int count = 0;
    //iternate through the buffer in reverse, look for when we cross the zero point, then count the number of samples before two further crosses. 
    for (int i = buffer.size() - 2; i > 0; i--){
        float sample = buffer[i];
        bool newSign = sample > zeroPoint;
        if (newSign != referenceSign) {
            debug("Sign changes: %d\n", signChange);
            signChange++;
            referenceSign = newSign;
            if (signChange > 0){
                count++;
            }
            if (signChange >= 3) {
                debug("Nr samples passed: %d\n", count);
                //using count, estimate the period of the wavelength...
                float period = 1.0/fs_hz * count;
                //return frequency
                float freq = 1.0/period;
                debug("Measured frequency: %f\n", freq);
                return freq;
            }
        }
    }
    //if algorithm was unsuccessful... ie lack of samples
    return -1.0;   
}


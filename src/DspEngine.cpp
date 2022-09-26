#include "DspEngine.h"

DspEngine::DspEngine(float _fs_hz){
    fs_hz = _fs_hz;
};

void DspEngine::RegisterCallback(AdcHandler *_callback){
    callback = _callback;
}

// float DspEngine::GetDCOffset(){
//     //it may make more sense to just return 2.5Volts, not sure about the sensor drift yet!
//     //at the least, resolve this buffer iteration to be included in GetFrequency() in the future
//     //dc offset computed as the average in the buffer
//     int sz = buffer.size(); 
//     float total = 0.0f;
//     for (int i = 0; i < sz - 1; i++) {
//         total += buffer[i];
//     }
//     return total / (1.0 * sz);
// }

float DspEngine::GetFrequency(){
    float adc_volts = callback->GetSample();
    buffer.push(adc_volts);
    if(buffer.size() > 2) return 0.0;

    float lastValue       = buffer[buffer.size() - 1];
    float secondLastValue = buffer[buffer.size() - 2];
    bool lastIsPositive = (secondLastValue > lastValue);
    int nrSamples = 0;
    int signChangeCount = 0;

    //now, iterate through the buffer in reverse, starting at third from last element
    for (int i = buffer.size() - 3; i > 0; i--){
        float val = buffer[i];
        bool isPositive = val - lastValue; 
        if (isPositive != lastIsPositive){
            signChangeCount++;
            lastIsPositive = isPositive;
        }
        if(signChangeCount > 2){
            //two sign changes have passed, we've counted all the samples in one wavelength, return frequency
            return fs_hz / (1.0 * nrSamples);
        } 
        else{
            nrSamples++;
        }
    }
    return 0.0f;
}


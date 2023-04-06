#include "DspEngine.h"
#include <Arduino.h>
#include <string.h>

#include "QuickFFT.h"
#include "ApproxFFT.h"

#include "DebugMonitor.h"


DspEngine::DspEngine(float _sample_interval_s){
    sample_interval_s =_sample_interval_s;
    internal_count = 0;
};

void DspEngine::RegisterCallback(AdcHandler *_callback){
    callback = _callback;
}

void DspEngine::RegisterFreqPtr(float* _freqPtr){
    freq_ptr = _freqPtr;
}

float DspEngine::GetFrequency(){
    //get adc sample
    int adc_value = callback->GetSample();
    //store sample at circular iteration in buffer
    buff[internal_count % FFT_BUFFER_SZ] = adc_value; 
    internal_count++;
    //very fast FFT on buffer, returns max frequency
    float freq = Q_FFT(buff, FFT_BUFFER_SZ, (1 / sample_interval_s));
    //set debug register 
    *freq_ptr = freq;

    //filter spurious values from quick fft
    //float processed_freq = sma_filter(freq, history);
    float processed_freq = freq;
    return processed_freq;
}


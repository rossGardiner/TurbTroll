#include <Arduino.h>

#include "Config.h"
#include "DebugMonitor.h"

#include "FreqInterruptHandler.h"


volatile unsigned int FreqInterruptHandler::pulse_count;

FreqInterruptHandler::FreqInterruptHandler(){
    pinMode(INT_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void FreqInterruptHandler::Begin(){
    attachInterrupt(digitalPinToInterrupt(INT_PIN), interrupt_routine, RISING);
//    noInterrupts();
}

void FreqInterruptHandler::RegisterFreqPtr(float* _freqPtr){
    freq_ptr = _freqPtr;
}


float FreqInterruptHandler::GetFreq(int delay_ms){
    pulse_count = 0;
    //interrupts();
    delay(delay_ms);
    //noInterrupts();
    float freq = (pulse_count) / (delay_ms / 1000.0);
    //float processed_freq = sma_filter(freq, history);
    *freq_ptr = freq;
    return freq;
}









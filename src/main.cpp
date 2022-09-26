#include <Arduino.h>
#include <Eventually.h>

#define LED_PIN 13  
#define ADC_PIN A0
#define SAMPLE_INTERVAL_MS 1000

#include "AdcHandler.h"
#include "DspEngine.h"

//global variables
EvtManager manager;
AdcHandler adcHandler(ADC_PIN);
DspEngine dspEngine(1.0/(SAMPLE_INTERVAL_MS));

void pullThrough(){
  float freq = dspEngine.GetFrequency();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(ADC_PIN, INPUT);

  dspEngine.RegisterCallback(&adcHandler);
  manager.addListener(new EvtTimeListener(SAMPLE_INTERVAL_MS, true, (EvtAction)pullThrough));
}

USE_EVENTUALLY_LOOP(manager)

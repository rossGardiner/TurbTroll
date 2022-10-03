#include <Arduino.h>
#include <Eventually.h>

#define LED_PIN 13  
#define ADC_PIN A0
#define SAMPLE_INTERVAL_MS 10

#include "DebugMonitor.h"
#include "AdcHandler.h"
#include "DspEngine.h"

//global variables
EvtManager manager;
AdcHandler adcHandler(ADC_PIN);
DspEngine dspEngine(1.0/(SAMPLE_INTERVAL_MS));

void pullThrough(){
  float freq = dspEngine.GetFrequency();
  debug("Freq detected: %f\n", freq);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ADC_PIN, INPUT);

  dspEngine.RegisterCallback(&adcHandler);
  manager.addListener(new EvtTimeListener(SAMPLE_INTERVAL_MS, true, (EvtAction)pullThrough));
}

USE_EVENTUALLY_LOOP(manager)


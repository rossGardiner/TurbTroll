#include <Arduino.h>
#include <Eventually.h>

#define ADC_PIN A0
#define SAMPLE_INTERVAL_MS 10

#include "DebugMonitor.h"
#include "AdcHandler.h"
#include "DspEngine.h"
#include "DecisionMaker.h"
#include "PwmHandler.h"

//global variables, processing pipeline
EvtManager manager;
AdcHandler adcHandler(ADC_PIN);
DspEngine dspEngine(1.0/(SAMPLE_INTERVAL_MS));
DecisionMaker decisionMaker(2, 1.0, 150.0, 600.0, 0.01);
PWMHander pwmHandler(LED_BUILTIN);

void pullThrough(){
  float dutyCycle = pwmHandler.UpdateDutyCycle();
  debug("Duty cycle: %f\n", dutyCycle);
}

void setup() {
  Serial.begin(115200);
  dspEngine.RegisterCallback(&adcHandler);
  decisionMaker.RegisterCallback(&dspEngine);
  pwmHandler.RegisterCallback(&decisionMaker);
  manager.addListener(new EvtTimeListener(SAMPLE_INTERVAL_MS, true, (EvtAction)pullThrough));
}

USE_EVENTUALLY_LOOP(manager)


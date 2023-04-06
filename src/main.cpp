#include <Arduino.h>
#include <Eventually.h>

#include "DebugMonitor.h"
#include "AdcHandler.h"
#include "DspEngine.h"
#include "DecisionMaker.h"
#include "PwmHandler.h"

#include "Config.h"

//global variables, processing pipeline
EvtManager manager;
AdcHandler adcHandler(ADC_PIN);
DspEngine dspEngine(SAMPLE_INTERVAL_US / 1000000.0);
DecisionMaker decisionMaker(0.001);
PWMHandler pwmHandler(PWM_PIN);

float global_frequency = -1.0;
float global_pwm_duty = 0.0;
DecisionState global_decision_state = DecisionState::FREESPIN; 

// void pullThrough(){
//   //f = dspEngine.GetFrequency();
//   //state = decisionMaker.speedStatus(f);
//   pwmHandler.UpdateDutyCycle();
// }

// void setup() {
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, HIGH);
//   dspEngine.RegisterCallback(&adcHandler);
//   decisionMaker.RegisterCallback(&dspEngine);
//   pwmHandler.RegisterCallback(&decisionMaker);

//   //set registers for value copies in global score
//   dspEngine.RegisterFreqPtr(&global_frequency);
//   decisionMaker.RegisterStatePtr(&global_decision_state);
//   pwmHandler.RegisterDutyPtr(&global_pwm_duty);

// }

// void loop(){
//   unsigned long m1 = micros();
//   pullThrough();
//   unsigned long diff = micros() - m1;
//   int d = 0;
//   if (diff < SAMPLE_INTERVAL_US){
//     d = SAMPLE_INTERVAL_US - diff;
//   }
//   delayMicroseconds(d);
// }

// void setup1(){
//   Serial.begin(115200);
//   Serial.println("Starting...");
// }

// float freq_to_rpm(float freq){
//   return 60 * freq / ((NR_POLES/2) * FREQ_DIVISION);
// }

// void loop1(){
//   delay(10);
//   debug("f: %f rpm: %f \r", global_frequency, freq_to_rpm(global_frequency));
// }


//constant 30% pwm test

// void setup(){
//   pinMode(LED_BUILTIN, OUTPUT);
//   pinMode(PWM_PIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, HIGH);
//   analogWriteFreq(100);
//   int asInt = 0.33 * 255;
//   analogWrite(PWM_PIN, asInt); 
//   //digitalWrite(PWM_PIN, HIGH);
 
// }

// void loop(){
//   // digitalWrite(PWM_PIN, HIGH);
//   // delayMicroseconds(3333);
//   // digitalWrite(PWM_PIN, LOW);
//   // delayMicroseconds(6667);
// }

// int pin = 2; 
// volatile unsigned int pulse; 
// const int pulses_per_litre = 450; 
 
// void count_pulse() 
// { 
// pulse++; 
// digitalWrite(LED_BUILTIN, pulse%2);
// } 

// void setup() 
// { 
// Serial.begin(115200); 

// pinMode(INT_PIN, INPUT);
// pinMode(LED_BUILTIN, OUTPUT);
// attachInterrupt(INT_PIN, count_pulse, RISING); 
// } 
 
// void loop() 
// { 
// pulse=0; 
// delay(1000); 
// noInterrupts(); 
// Serial.print("Pulses per second: "); 
// Serial.println(pulse); 
// interrupts(); 

// } 

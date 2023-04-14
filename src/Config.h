#ifndef TURBTROLL_CONFIG_H
#define TURBTROLL_CONFIG_H

#include <Arduino.h>

//debug config
// 1 - debugging on; 0 - debugging off
#define DEBUG 1 

//device config
#define ADC_PIN A0
#define INT_PIN D19
#define SAMPLE_INTERVAL_US 1500
#define FREQ_DIVISION 2 //pulse is half-rectified
#define PWM_PIN D16
#define PWM_FREQ 5.0
#define BRAKE_PIN D17

//program config
#define FFT_BUFFER_SZ 256

//turbine config
//nr poles 
#define NR_POLES 10
//min RPM, below this just free spin (disconnect load)
#define MIN_RPM 100.0
//RPM for full modulation
#define FULL_MOD_RPM 600.0 
//Absolute max RPM, beyond this, brake the turbine, software makes every effort not to exceed this speed limit.
#define MAX_RPM 1000.0

//timings
#define UPDATE_INTERVAL_MS 500
//brake hold time (default for 15 mins)
#define BRAKE_HOLD_MS 15UL * 60UL * 1000UL

#endif
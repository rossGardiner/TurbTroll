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
#define FREQ_DIVISION 2
#define PWM_PIN D16
#define PWM_FREQ 100

//program config
#define FFT_BUFFER_SZ 256

//turbine config
//nr poles 
#define NR_POLES 10
//min RPM, below this just free spin (disconnect load)
#define MIN_RPM 100.0
//max RPM, above this just free spin (disconnect load)
#define MAX_RPM 600.0 
//target RPM, try to control the turbine to this speed
#define TARGET_RPM 325.0

#endif
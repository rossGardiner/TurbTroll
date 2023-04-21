#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
void LCDUpdate();

// Init timers for low freq pwm, for now this must be done in main.cpp
#include "RPi_Pico_TimerInterrupt.h"
#include "RP2040_Slow_PWM.h"
#define HW_TIMER_INTERVAL_US 10000L
RP2040_Timer ITimer(0);
RP2040_Slow_PWM ISR_PWM;
bool TimerHandler(struct repeating_timer *t)
{ 
  ISR_PWM.run();
  return true;
}

#include "DebugMonitor.h"
#include "FreqInterruptHandler.h"
#include "DecisionMaker.h"
#include "PwmHandler.h"


#include "Config.h"

//global variables, processing pipeline
FreqInterruptHandler freqInterruptHandler;
DecisionMaker decisionMaker(UPDATE_INTERVAL_MS);
PWMHandler pwmHandler(PWM_PIN);
BrakeHandler brakeHandler(BRAKE_PIN);

float global_frequency = -1.0;
float global_pwm_duty = 0;
DecisionState global_decision_state = DecisionState::FREESPIN; 

void pullThrough(){
    pwmHandler.UpdateDutyCycle();
}
int channelNum;
void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
      pinMode(LED_BUILTIN, OUTPUT);
    //digitalWrite(LED_BUILTIN, HIGH);
    Serial.begin();
    freqInterruptHandler.Begin();

    //register callbacks
    decisionMaker.RegisterFrequencyCallback(&freqInterruptHandler);
    decisionMaker.RegisterBrakeCallback(&brakeHandler);
    pwmHandler.RegisterCallback(&decisionMaker);

    //register debug pointers
    freqInterruptHandler.RegisterFreqPtr(&global_frequency);
    decisionMaker.RegisterStatePtr(&global_decision_state);
    pwmHandler.RegisterDutyPtr(&global_pwm_duty);

    //pwm config
    ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_US, TimerHandler);
    channelNum = ISR_PWM.setPWM(PWM_PIN, PWM_FREQ, (float)(global_pwm_duty));
}

void loop(){
    //pull through pipeline
    pullThrough();
    //update output pwm
    ISR_PWM.modifyPWMChannel(channelNum, PWM_PIN, PWM_FREQ, (float)(global_pwm_duty));
}

void setup1(){
    Serial.begin(115200);
    printf("Starting...");
    lcd.init();                      // initialize the lcd 
    lcd.backlight();

}

float hzToRpm(float hz){
    return 60.0 * hz / ((NR_POLES/2) * FREQ_DIVISION);
}

void loop1(){
    delay(10);
    LCDUpdate();
    printf("f: %f, rpm: %f, state: %d, duty: %f \n", global_frequency, hzToRpm(global_frequency), global_decision_state, global_pwm_duty);

}

char lcd_line[256];
char* blank_line = "                   ";
void LCDUpdate(){
  lcd.setCursor(0,0);
  lcd.print(blank_line);
  lcd.setCursor(0,0);
  sprintf(lcd_line, "RPM: %.0f F: %.1f", hzToRpm(global_frequency), global_frequency);
  lcd.print(lcd_line);
  
  lcd.setCursor(0,1);
  switch(global_decision_state){
    case DecisionState::FREESPIN:
      sprintf(lcd_line, "State: FREESPIN");
      break;
    case DecisionState::MODULATING:
      sprintf(lcd_line, "State: MODULATING");
      break;
    case DecisionState::BRAKE:
      sprintf(lcd_line, "State: BRAKE");
      break;
    default:
      sprintf(lcd_line, "State: ERROR");
      
  }
  lcd.print(blank_line);
  lcd.setCursor(0,1);
  lcd.print(lcd_line);
  lcd.setCursor(0,2);
  lcd.print(blank_line);
  lcd.setCursor(0,2);
  sprintf(lcd_line, "Mod. Duty: %.2f", global_pwm_duty);
  lcd.print(lcd_line);
}





/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 * YWROBOT
 *Compatible with the Arduino IDE 1.0
 *Library version:1.1







// /*********
//   Rui Santos
//   Complete project details at https://randomnerdtutorials.com  
//   Based on the Dallas Temperature Library example
// *********/
// #include "Config.h"
// #include "one_wire.h"

// #define SENSOR_DATA D1

// One_wire one_wire(SENSOR_DATA);
// rom_address_t address{};
// void printAddress(rom_address_t &deviceAddress);


// void setup() {
//     pinMode(SENSOR_DATA, INPUT);
//     Serial.begin(115200);
//     one_wire.init();
// }

// void loop() {
//     one_wire.single_device_read_rom(address);
//     Serial.print("Address: ");
//     printAddress(address);
//     Serial.println();
//     one_wire.convert_temperature(address, true, false);
//     Serial.print("Temperature: ");
//     Serial.println(one_wire.temperature(address));
//     sleep_ms(1000);
// }

// void printAddress(rom_address_t &deviceAddress) {
//   for (uint8_t i = 0; i < 8; i++)
//   {
//     // zero pad the address if necessary
//     if (deviceAddress.rom[i] < 16) Serial.print("0");
//     Serial.print(deviceAddress.rom[i], HEX);
//   }
// }


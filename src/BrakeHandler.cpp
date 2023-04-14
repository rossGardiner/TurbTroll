#include <Arduino.h>

#include "Config.h"

#include "BrakeHandler.h"

BrakeHandler::BrakeHandler(int _brakePin){
    brakePin = _brakePin;
    pinMode(brakePin, OUTPUT);
}

void BrakeHandler::Brake(){
    digitalWrite(brakePin, HIGH);
}

void BrakeHandler::BrakeHold(int hold_ms){
    Brake();
    noInterrupts();
    delay(hold_ms);
    interrupts();
    Release();
}

void BrakeHandler::Release(){
    digitalWrite(brakePin, LOW);
}
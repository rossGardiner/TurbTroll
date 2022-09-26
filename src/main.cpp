#include <Arduino.h>
#include <Eventually.h>
#define LED 13  

//global variables
EvtManager manager;
int state = 0;

bool blink_handler(){
  state = !state; // Switch light states
  digitalWrite(LED, state); // Display the state
  return false; // Allow the event chain to continue
}

void setup() {
  pinMode(LED, OUTPUT);
  manager.addListener(new EvtTimeListener(1000, true, (EvtAction)blink_handler));
}

USE_EVENTUALLY_LOOP(manager)

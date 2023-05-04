#include <Wire.h>
#include <Zumo32U4.h>
#include <Zumo32U4LineSensors.h>
#include "lijn.h"


lijn Lijn;


void setup() {

  Serial.begin(9600);
}


void loop() {
  static uint16_t lastSampleTime = 0;
  if ((uint16_t)(millis() - lastSampleTime) >= 100)
  {
    lastSampleTime = millis();
    Lijn.print_waardes();
  }
}

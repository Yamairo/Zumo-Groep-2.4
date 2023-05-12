#include <Wire.h>
#include <Zumo32U4.h>
#include <Zumo32U4LineSensors.h>
#include "lijn.h"


lijn Lijn;


void setup() {

  Serial.begin(9600);
}


void loop() {
  int tijd = 0;
  if ((millis() - tijd) >= 100)
  {
    lastSampleTime = millis();
    Lijn.print_waardes();
  }
s}

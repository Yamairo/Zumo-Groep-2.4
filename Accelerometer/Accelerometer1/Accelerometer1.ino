#include "Accelerometer.h"

Accelerometer accel;

void setup() {
  accel.sensorenInitialiseren();
}

void test() {
  Serial.println("bergop");
} 

void test2() {
  Serial.println("bergaf");
} 


void loop() {
  // accel.snelheidsverschilBerekenen();
  // accel.botsingControleren();
  // accel.controleerLinksRechtsBeweging();
  accel.brugKantelingDetecteren(test, test2);
}

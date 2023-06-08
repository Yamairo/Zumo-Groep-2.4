// #include <Wire.h>
// #include <Zumo32U4.h>
// #include "prox.h"
// #include "Motor.h"

// ProximitySensors sensors;
// Motor motor;

// void setup() {
//   // put your setup code here, to run once:
//   Wire.begin();
//   sensors.read();
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   sensors.read();
//   uint16_t i = sensors.getMiddle();
//   Serial.println(i);
  
//   while (sensors.getMiddle() > 9) {
//     delay(100);
//     motor.stopMotors();
//     motor.rechteLijn();
//   }
  
//   if (sensors.getLeft() > sensors.getRight()) {
//     motor.draaiLinks();
//   } else {
//     motor.draaiRechts();
//   }
// }

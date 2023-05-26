#include "Motor.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "lijn.h"

Accelerometer accel;
Motor motor;
Magnetometer magnet;
lijn Lijn;
Zumo32U4ButtonB Knop;

bool buttonPress = Knop.getSingleDebouncedPress();
void setup() {
  Serial.begin(9600);
  while(!Knop.isPressed()){
    delay(1);
  }
  Lijn.calibrate_test();
  accel.sensorenInitialiseren();
  magnet.init();
}


void loop() {
  int tijd = 0;
  if ((millis() - tijd) >= 100) {
    tijd = millis();
    Lijn.print_waardes();
  }
  if(accel.brugKantelingDetecteren()){
    motor.rechteLijn();
  }
  else {
    motor.stop();
  }
  magnet.geefWaardes();
  motor.test();
}


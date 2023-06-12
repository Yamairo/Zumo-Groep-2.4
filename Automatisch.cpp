#include "Automatisch.h"

Automatisch::Automatisch(){
  Serial1.begin(9600);
}
Automatisch::~Automatisch(){}

void Automatisch::init(){
  while(!Knop.isPressed()){
    delay(1);
  }
  accel.sensorenInitialiseren();
  magnet.init();
}

void Automatisch::brugAfrijden(){
  if(accel.brugKantelingDetecteren()){
      motor.rechteLijn();
    }
    else {
      motor.stop();
    }
}

void Automatisch::duwBlokje(){
  while (sensors.getMiddle() > 9) {
      delay(100);
      motor.stopMotors();
      motor.rechteLijn();
    if (sensors.getLeft() > sensors.getRight()) {
      motor.draaiLinks();
    } else {
      motor.draaiRechts();
    }
      motor.test();
  }
}

void Automatisch::vindLijn(){
  Lijn.lineSensors.readCalibrated(Lijn.lineSensorValues, QTR_EMITTERS_ON);
  if (Lijn.lineSensorValues[1] > 500) {
      motor.zetSnelheid(150, 150);
  }
  else{
    motor.stop();
  }
}

void Automatisch::volgLijn(){
  vindLijn();
  int16_t position = lineSensors.readLine(lineSensorValues);
  int16_t error = position - 2000;
  int16_t speedDifference = error / 4 + 6 * (error - lastError);
  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}
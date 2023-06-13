#include "Arduino.h"
#include "HardwareSerial.h"
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
  Serial1.println(Lijn.handmatig_kleuren_midden());
  if(Lijn.handmatig_kleuren_midden() == Lijn.ZWART) {
    motor.zetSnelheid(150, 150);
    delay(150);
  }
  else{
    motor.stop();
  }
}

void Automatisch::volgLijn(){
  // vindLijn();
  // if (Lijn.handmatig_kleuren_midden() != Lijn.ZWART) {
  //   int t1 = millis();
  //   int t2 = t1 + 100;
  //   while ((millis() < t2 && Lijn.handmatig_kleuren_midden() != Lijn.ZWART)) {
  //     motor.draaiLinks();
  //   }
  //   while (millis() < t2*2 && Lijn.handmatig_kleuren_midden()) {
  //     motor.draaiRechts();
  //   }
  // }
  // Get the position of the line.  Note that we *must* provide
  // the "lineSensorValues" argument to readLine() here, even
  // though we are not interested in the individual sensor
  // readings.
  int16_t position = Lijn.lineSensors.readLine(Lijn.lineSensorValues);

  // Our "error" is how far we are away from the center of the
  // line, which corresponds to position 2000.
  int16_t error = position - 1000;

  // Get motor speed difference using proportional and derivative
  // PID terms (the integral term is generally not very useful
  // for line following).  Here we are using a proportional
  // constant of 1/4 and a derivative constant of 6, which should
  // work decently for many Zumo motor choices.  You probably
  // want to use trial and error to tune these constants for your
  // particular Zumo and line course.
  int16_t speedDifference = error / 1 + 8 * (error - lastError);

  lastError = error;

  // Get individual motor speeds.  The sign of speedDifference
  // determines if the robot turns left or right.
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  // Constrain our motor speeds to be between 0 and maxSpeed.
  // One motor will always be turning at maxSpeed, and the other
  // will be at maxSpeed-|speedDifference| if that is positive,
  // else it will be stationary.  For some applications, you
  // might want to allow the motor speed to go negative so that
  // it can spin in reverse.
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}


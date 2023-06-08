#include "Motor.h"

Motor::Motor() {
  buttonPress = Knop.getSingleDebouncedPress(); // initialize buttonPress in constructor
}

void Motor::rechteLijn(){
  Motor.setLeftSpeed(200); // set left motor speed to 200 (out of 400)
  Motor.setRightSpeed(200); // set right motor speed to 200 (out of 400)
}

void Motor::zetSnelheid(int snelheidRechts, int snelheidLinks){
  Motor.setLeftSpeed(snelheidLinks);
  Motor.setRightSpeed(snelheidRechts);
}


void Motor::stop(){
  Motor.setLeftSpeed(0); // stop left motor
  Motor.setRightSpeed(0); // stop right motor
}

void Motor::test() {
  buttonPress = Knop.getSingleDebouncedPress();

  if (buttonPress) {
  Motor.setLeftSpeed(200); // set left motor speed to 200 (out of 400)
  Motor.setRightSpeed(200); // set right motor speed to 200 (out of 400)
  delay(1000); // move forward for 1 second
  Motor.setLeftSpeed(0); // stop left motor
  Motor.setRightSpeed(0); // stop right motor
  delay(100); // pause for 1 second
  }
}

void Motor::rijVooruit() {
  Motor.setSpeeds(motorspeed, motorspeed);
}

void Motor::rijAchteruit() {
  Motor.setSpeeds(-motorspeed, -motorspeed);
}

void Motor::draaiLinks() {
  Motor.setSpeeds(-motorspeed, motorspeed);
}

void Motor::draaiRechts() {
  Motor.setSpeeds(motorspeed, -motorspeed);
}

void Motor::stopMotors() {
  Motor.setSpeeds(0, 0);
}

void Motor::RechtsVooruit() {
Motor.setSpeeds(motorspeed+200, motorspeed);
}

void Motor::RechtsAchteruit() {
  Motor.setSpeeds(-motorspeed-200, -motorspeed);
}

void Motor::LinksVooruit() {
  Motor.setSpeeds(motorspeed, motorspeed+200);
}

void Motor::LinksAchteruit() {
  Motor.setSpeeds(-motorspeed, -motorspeed-200);
}

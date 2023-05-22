#include "Motor.h"

Motor::Motor() {
  buttonPress = Knop.getSingleDebouncedPress(); // initialize buttonPress in constructor
}

void Motor::init(){
  Motor.flipLeftMotor(true); // reverse left motor direction
  Motor.flipRightMotor(true); // reverse right motor direction
}


void Motor::test() {
  buttonPress = Knop.getSingleDebouncedPress();

  if (buttonPress) {
  Motor.setLeftSpeed(-200); // set left motor speed to 200 (out of 400)
  Motor.setRightSpeed(-200); // set right motor speed to 200 (out of 400)
  delay(1000); // move forward for 1 second
  Motor.setLeftSpeed(0); // stop left motor
  Motor.setRightSpeed(0); // stop right motor
  delay(100); // pause for 1 second
  }
}

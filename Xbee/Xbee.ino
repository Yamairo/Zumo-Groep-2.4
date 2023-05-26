#include <Wire.h>
#include <Zumo32U4.h>
#include "Xbee.h"

Zumo32U4Motors motors;
const int MOTOR_SPEED = 150;
const int MOTOR_SPEED2 = 100;


// #include <Zumo32U4Buttons.h>

using namespace std;

// Zumo32U4ButtonA buttonA;
XBee xbee1;

/*!test file */
void setup() {
    // Serial.begin(9600);
  Serial1.begin(9600); // Initialize Serial1 for communication with XBee

  // Enable Timer4 for motor control
  TCCR4A = 0;
  TCCR4B = 1 << CS41;
  TCCR4D = 1 << WGM40;
}


void loop() {
   /*!stuurt data*/
  if (Serial1.available()) {
    char command = xbee1.receive();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'W':
      driveForward();
      break;
    case 'A':
      turnLeft();
      break;
    case 'S':
      driveBackward();
      break;
    case 'D':
      turnRight();
      break;
    case 'X':
      stopMotors();
      break;
    default:
      break;
  }
}

void driveForward() {
  motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
}

void driveBackward() {
  motors.setSpeeds(-MOTOR_SPEED, -MOTOR_SPEED);
}

void turnLeft() {
  motors.setSpeeds(-MOTOR_SPEED2, MOTOR_SPEED2);
}

void turnRight() {
  motors.setSpeeds(MOTOR_SPEED2, -MOTOR_SPEED2);
}

void stopMotors() {
  motors.setSpeeds(0, 0);
}



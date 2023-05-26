#include <Wire.h>
#include <Zumo32U4.h>
#include <Zumo32U4LineSensors.h>
#include "lijn.h"
#include "XBee.h"


lijn Lijn;
XBee xbee1;
Zumo32U4Motors motors;
Zumo32U4ButtonB Knop;
Zumo32U4ButtonA Handmatig;
Zumo32U4ButtonC Automaat;

const int MOTOR_SPEED = 200;
bool automatisch = true;

bool buttonPress = Knop.getSingleDebouncedPress();
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
  }}
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Initialize Serial1 for communication with XBee
  while(!Knop.isPressed()){
    delay(1);
  }
  Lijn.calibrate_test();

  // Enable Timer4 for motor control
  TCCR4A = 0;
  TCCR4B = 1 << CS41;
  TCCR4D = 1 << WGM40;
}


void loop() {
  if(Handmatig.isPressed()){
    automatisch = false;
  }
  else if (Automaat.isPressed()) {
    automatisch = true;
  }
  else if(!automatisch){
    // Code voor handmatige besturing 
      if (Serial1.available()) {
      char command = xbee1.receive();
      executeCommand(command);
      Serial.print("1");
    } 
  }
  if(automatisch){
    // Code voor automatisch rijden
    int tijd = 0;
    if ((millis() - tijd) >= 100) {
      tijd = millis();
      Lijn.print_waardes();
      Serial.print("2");
    }
  }
}


void driveForward() {
  motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
}

void driveBackward() {
  motors.setSpeeds(-MOTOR_SPEED, -MOTOR_SPEED);
}

void turnLeft() {
  motors.setSpeeds(-MOTOR_SPEED, MOTOR_SPEED);
}

void turnRight() {
  motors.setSpeeds(MOTOR_SPEED, -MOTOR_SPEED);
}

void stopMotors() {
  motors.setSpeeds(0, 0);
}



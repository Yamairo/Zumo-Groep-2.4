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
  while (sensors.getMiddle() > 3) {
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

void Automatisch::volgLijn(int errorOffset, int errorProportioneleConstante, int errorAfgeleideConstante, int maxSpeed){
  int position = Lijn.lineSensors.readLine(Lijn.lineSensorValues);
  int error = position - errorOffset;
  int speedDifference = error / errorProportioneleConstante + errorAfgeleideConstante * (error - lastError);

  lastError = error;

  int leftSpeed = (int16_t)maxSpeed + speedDifference;
  int rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}

void Automatisch::sturenMetGrijzeLijn(){
//   if(Lijn.handmatig_kleuren_links() == Lijn.GRIJS){
//     vindLijn();
//   if (Lijn.handmatig_kleuren_midden() != Lijn.ZWART) {
//     int t1 = millis();
//     int t2 = t1 + 100;
//   while ((millis() < t2 && Lijn.handmatig_kleuren_midden() != Lijn.ZWART)) {
//     motor.draaiLinks();
//   }
//   while (millis() < t2*2 && Lijn.handmatig_kleuren_midden()) {
//     motor.draaiRechts();
//   }
// }
//   }
//   if(Lijn.handmatig_kleuren_rechts() == Lijn.GRIJS){
//     vindLijn();
//     if (Lijn.handmatig_kleuren_midden() != Lijn.ZWART) {
//       int t1 = millis();
//       int t2 = t1 + 100;
//       while ((millis() < t2 && Lijn.handmatig_kleuren_midden() != Lijn.ZWART)) {
//         motor.draaiLinks();
//       }
  
//     }
//   }
  if(Lijn.handmatig_kleuren_midden() == Lijn.GROEN) {
    motor.stop();
    Serial1.println("GRIJS");
    errorOffset = 1000;
    errorProportioneleConstante = 1;
    errorAfgeleideConstante = 8;
    maxSpeed = 150;
  }
  else {
    motor.stop();
    errorOffset = 1000;
    errorProportioneleConstante = 1;
    errorAfgeleideConstante = 8;
    maxSpeed = 200;
    Serial1.println("ELSE!!!!");
  }
  volgLijn(errorOffset, errorProportioneleConstante, errorAfgeleideConstante, maxSpeed);
  delay(100);
}


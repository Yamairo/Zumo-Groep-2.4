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

void Automatisch::volgLijn(){
  Lijn.lineSensors.readCalibrated(Lijn.lineSensorValues, QTR_EMITTERS_ON);
  Serial1.println(Lijn.lineSensorValues[1]);
  if (Lijn.lineSensorValues[1] > 600) {
      motor.rechteLijn();
  }
  if {
    
  }
}
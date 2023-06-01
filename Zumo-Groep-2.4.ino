#include "Motor.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "lijn.h"
#include "XBee.h"
#include "Handmatig.h"

// Hieronder volgen alle klassen die nodig zijn voor het besturen van de zumo
Accelerometer accel;
Handmatig hand;
Motor motor;
Magnetometer magnet;
Lijn Lijn;
XBee xbee1;
Zumo32U4Motors motors;
Zumo32U4ButtonB Knop;
Zumo32U4ButtonA Automaat;
Zumo32U4ButtonC Handmatig;

// Deze boolean wordt gebruikt om de zumo te wissel tussen handmatige en automatische besturing
bool automatisch = false;

bool buttonPress = Knop.getSingleDebouncedPress();
// void executeCommand(char command) {
//   /*!
//    * \brief Geeft de besturings commandos door.
//    *
//    * Door het sturen van "W", "A", "S", "D", "X" kan je de zumo besturen
//    * hiebij is W vooruit; A linksom draaien; S achteruit rijden; D rechtsom draaien;
//    * X voor het stoppen van de motoren.
//    */
//   switch (command) {
//     case 'W':
//       motor.rijVooruit();
//       break;
//     case 'A':
//       motor.draaiLinks();
//       break;
//     case 'S':
//       motor.rijAchteruit();
//       break;
//     case 'D':
//       motor.draaiRechts();
//       break;
//     case 'X':
//       motor.stopMotors();
//       break;
//     default:
//       break;
//   }
// }

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Initialize Serial1 for communication with XBee
  while(!Knop.isPressed()){
    delay(1);
  }
  Lijn.calibrate_test();
  accel.sensorenInitialiseren();
  magnet.init();
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
      hand.HandmatigeBesturing(command);
      Serial.print("1");
    } 
  }
  if(automatisch){
    // Code voor automatisch rijden
    // De code hieronder is voor de lijnsensor waardes

    // int tijd = 0;
    // if ((millis() - tijd) >= 100) {
    //   tijd = millis();
    //   Lijn.print_waardes();
    //   Serial.print("2");
    // }

    if(accel.brugKantelingDetecteren()){
      motor.rechteLijn();
    }
    else {
      motor.stop();
      magnet.geefWaardes();
    }
    motor.test();
  }
}




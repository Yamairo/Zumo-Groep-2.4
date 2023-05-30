/*!
 * \file Zumo-Groep-2.4.ino
 * \brief Bevat de code voor het besturen van de zumo
 * \author [Yamairo Martinus]
 * \date [30-5-2023]
 */

/*!
 * \mainpage Accelerometer Klasse Documentatie
 *
 * \section intro_sec Inleiding
 *
 * Deze documentatie beschrijft de klasses die gebruikt zijn voor het besturen van de zumo.
 *
 * \section installatie_sec Installatie
 *
 * Deze klas is bedacht op bassis van de Zumo libraries daarom is het van belang dat je de volgende libraries hebt:
 * - Wire.h
 * - Zumo32U4.h
 * - 
 *
 * \section gebruik_sec Gebruik
 *
 * Om deze code te gebruiken zal je een zumo en een xbee nodig hebben. Daarna zal deze code geupload moeten worden op de zumo.
 * Als dit is gedaan zal je moeten wisselen naar de port van de xbee om de zumo te besturen via de serial input.
 *
 * Voor meer gedetailleerde informatie over de functies van de klassen, zie de documentatie van de individuele functies.
 */
#include "Motor.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "lijn.h"
#include "XBee.h"
// Hieronder volgen alle klassen die nodig zijn voor het besturen van de zumo
Accelerometer accel;
Motor motor;
Magnetometer magnet;
lijn Lijn;
XBee xbee1;
Zumo32U4Motors motors;
Zumo32U4ButtonB Knop;
Zumo32U4ButtonA Automaat;
Zumo32U4ButtonC Handmatig;

// Deze boolean wordt gebruikt om de zumo te wissel tussen handmatige en automatische besturing
bool automatisch = false;

bool buttonPress = Knop.getSingleDebouncedPress();
void executeCommand(char command) {
  /*!
   * \brief Geeft de besturings commandos door.
   *
   * Door het sturen van "W", "A", "S", "D", "X" kan je de zumo besturen
   * hiebij is W vooruit; A linksom draaien; S achteruit rijden; D rechtsom draaien;
   * X voor het stoppen van de motoren.
   */
  switch (command) {
    case 'W':
      motor.rijVooruit();
      break;
    case 'A':
      motor.draaiLinks();
      break;
    case 'S':
      motor.rijAchteruit();
      break;
    case 'D':
      motor.draaiRechts();
      break;
    case 'X':
      motor.stopMotors();
      break;
    default:
      break;
  }
}

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
      executeCommand(command);
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




#include "Automatisch.h"
Automatisch automatisch;
Handmatig hand;
// Deze boolean wordt gebruikt om de zumo te wissel tussen handmatige en automatische besturing

bool automatische_modus = false;
XBee xbee1;
Zumo32U4ButtonA Automaat;
Zumo32U4ButtonC KnopHandmatig;
Zumo32U4LineSensors lineSensors;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Initialize Serial1 for communication with XBee
  automatisch.init();
  automatisch.Lijn.calibrate_test();
}


void loop() {
  if(KnopHandmatig.isPressed()){
    automatische_modus = false;
  }
  else if (Automaat.isPressed()) {
    automatische_modus = true;
  } 
  else if(!automatische_modus){
    // Code voor handmatige besturing 
      if (Serial1.available()) {
      char command = xbee1.receive();
      hand.HandmatigeBesturing(command);
      Serial.print("1");
    } 
  }
  if(automatische_modus){
    // Code voor automatisch rijden
    Serial1.println(automatisch.Lijn.lineSensorValues[1]);
    Automatisch.brugAfrijden();
    automatisch.volgLijn();
    if(false){
      automatisch.duwBlokje();
    }
  } 
}




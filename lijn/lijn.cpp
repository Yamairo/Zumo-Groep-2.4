#include "lijn.h"
#include <Zumo32U4.h>

lijn::lijn() {
  lineSensors.initThreeSensors();
}

lijn::~lijn() {

}

int lijn::lees_waarde() {
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  return lineSensorValues;
}


// Dit is een debug/test dingetje, niet voor gebruik in het uitendelijke ontwerp
void lijn::print_waardes() {
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  Serial.print("SL: ");
  Serial.print(lineSensorValues[0]);
  Serial.print(",");
  Serial.print("SM: ");
  Serial.print(lineSensorValues[1]);
  Serial.print(",");
  Serial.print("SR: ");
  Serial.println(lineSensorValues[2]);
}

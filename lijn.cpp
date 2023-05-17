#include "lijn.h"
#include <Zumo32U4.h>

lijn::lijn() {
  lineSensors.initThreeSensors();
}

lijn::~lijn() {

}

// Lees de waardes uit van de sensoren.
// De waardes worden in lineSensorValues gezet en teruggegeven. 
int lijn::lees_waarde(bool kalibreer) {
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  if (calibreer){ // Gebruikt de offsets om de sensorwaardes te kalibreren
      // TODO: eventueel herschrijven om map() (arduino.h) te gebruiken
      lineSensorValues[0] = lineSensorValues[0] + SENSOR_LINKS_OFFSET;
      lineSensorValues[1] = lineSensorValues[1] + SENSOR_MIDDEN_OFFSET;
      lineSensorValues[2] = lineSensorValues[2] + SENSOR_RECHTS_OFFSET;
  }
  return lineSensorValues;
}


// Dit is een debug/test dingetje, niet voor gebruik in het uitendelijke ontwerp
void lijn::print_ruwe_waardes() {
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

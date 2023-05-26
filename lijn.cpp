#include "lijn.h"
#include <Zumo32U4.h>

lijn::lijn() {
  lineSensors.initThreeSensors(); // Initaliseer de klasse
 // delay(1000);
  //calibrate_test();
}

lijn::~lijn() {

}

void lijn::calibrate_test() {
  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  
  //delay(1000);
  for (uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }
    Serial.println("Kaliberen!");
    lineSensors.calibrate(QTR_EMITTERS_ON);
  }
  motors.setSpeeds(0, 0);

}

// Lees de waardes uit van de sensoren.
// De waardes worden in lineSensorValues gezet en teruggegeven.
int lijn::lees_waarde() {  motors.setSpeeds(0, 0);

  //lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  lineSensors.readCalibrated(lineSensorValues, QTR_EMITTERS_ON);
  return lineSensorValues;
}



// Dit is een debug/test dingetje, niet voor gebruik in het uitendelijke ontwerp
void lijn::print_waardes() {
  lineSensors.readCalibrated(lineSensorValues, QTR_EMITTERS_ON);
  Serial.print("SL: ");
  Serial.print(lineSensorValues[0]);
  Serial.print(",");
  Serial.print("SM: ");
  Serial.print(lineSensorValues[1]);
  Serial.print(",");
  Serial.print("SR: ");
  Serial.println(lineSensorValues[2]);
}

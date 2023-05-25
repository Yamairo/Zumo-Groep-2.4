#include "lijn.h"
#include <Zumo32U4.h>
#include <Zumo32U4Motors.h>
void calibrateSensors()
{
    Zumo32U4Motors motors;
    Zumo32U4LineSensors lineSensors;
  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
}

lijn::lijn() {
  lineSensors.initThreeSensors(); // Initaliseer de klasse

  calibrateSensors();
}

lijn::~lijn() {

}

// Lees de waardes uit van de sensoren.
// De waardes worden in lineSensorValues gezet en teruggegeven.
int lijn::lees_waarde() {
  //lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  lineSensors.readCalibrated(lineSensorValues, QTR_EMITTERS_ON);
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

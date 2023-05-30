#include "lijn.h"
#include <Zumo32U4.h>

Lijn::Lijn() {
  lineSensors.initThreeSensors();  // Initaliseer de klasse
                                   // delay(1000);
  //calibrate_test();
}

Lijn::~Lijn() {
}

void Lijn::calibrate_test() {
  // De robot draait heen en weer om de sensor een goede maximale en minimale waarde te geven
  // Daarna wordt de sensor gekalibreerd

  delay(100);
  for (uint16_t i = 0; i < 120; i++) {
    if (i > 30 && i <= 90) {
      //motor.zetSnelheid(-200, 200);
      motors.setSpeeds(-200, 200);
    } else {
      //motors.setSpeeds(200, -200);
      motor.zetSnelheid(200, -200);
    }
    Serial.println("Kaliberen!");
    lineSensors.calibrate(QTR_EMITTERS_ON);
  }
  motor.zetSnelheid(0, 0);
  //motors.setSpeeds(0, 0);
}

// Lees de waardes uit van de sensoren.
// De waardes worden in lineSensorValues gezet en teruggegeven.
int Lijn::lees_waarde() {
  motors.setSpeeds(0, 0);

  //lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  lineSensors.readCalibrated(lineSensorValues, QTR_EMITTERS_ON);
  return lineSensorValues;
}



// Dit is een debug/test dingetje, niet voor gebruik in het uitendelijke ontwerp
void Lijn::print_waardes() {
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


#include "USBAPI.h"
#include "Arduino.h"
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
  //motors.setSpeeds(0, 0);

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


int Lijn::check_kleur(int links, int midden, int rechts) {

  Lijn::lees_waarde();
  //lineSensors.readCalibrated(lineSensorValues, QTR_EMITTERS_ON);
  //lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);

  /*
* De waardes die via de sensor binnenkomen zijn niet correct; 
* Waarschijnlijk gaat het in de calibratie ergens fout
* nu gewoon met vaste waardes proberen. Misschien werkt dat beter, en anders weet ik het ook niet meer. 
*/

  int l_kleur, m_kleur, r_kleur;
  if (is_binnen_bounds(lineSensorValues[0], kalibratie_grijs[0])) {
    l_kleur = GRIJS;
  } else if (is_binnen_bounds(lineSensorValues[0], kalibratie_zwart[0])) {
    l_kleur = ZWART;
  } else if (is_binnen_bounds(lineSensorValues[0], kalibratie_groen[0])) {
    l_kleur = GROEN;
  }

  if (is_binnen_bounds(lineSensorValues[1], kalibratie_zwart[1])) {
    m_kleur = ZWART;
  } else if (is_binnen_bounds(lineSensorValues[1], kalibratie_zwart[1])) {
    m_kleur = GROEN;
  }

  if (is_binnen_bounds(lineSensorValues[2], kalibratie_grijs[2])) {
    r_kleur = GRIJS;
  } else if (is_binnen_bounds(lineSensorValues[2], kalibratie_zwart[2])) {
    r_kleur = ZWART;
  } else if (is_binnen_bounds(lineSensorValues[2], kalibratie_groen[2])) {
    r_kleur = GROEN;
  }
  links = l_kleur;
  midden = m_kleur;
  rechts = r_kleur;
  return links, midden, rechts;
}

bool Lijn::kalibreer_kleuren() {
  Serial.println("Bruin");
  wacht_op_bevestiging();
  Lijn::lees_waarde();
  kalibratie_bruin[1] = lineSensorValues[1];
  kalibratie_bruin[2] = lineSensorValues[2];
  kalibratie_bruin[3] = lineSensorValues[3];

  Serial.print("SLK: ");
  Serial.print(kalibratie_bruin[0]);
  Serial.print(",");
  Serial.print("SMK: ");
  Serial.print(kalibratie_bruin[1]);
  Serial.print(",");
  Serial.print("SRK: ");
  Serial.println(kalibratie_bruin[2]);

  Serial.println("Groen");
  wacht_op_bevestiging();
  Lijn::lees_waarde();
  kalibratie_groen[1] = lineSensorValues[1];
  kalibratie_groen[2] = lineSensorValues[2];
  kalibratie_groen[3] = lineSensorValues[3];

  Serial.print("SLK: ");
  Serial.print(kalibratie_groen[0]);
  Serial.print(",");
  Serial.print("SMK: ");
  Serial.print(kalibratie_groen[1]);
  Serial.print(",");
  Serial.print("SRK: ");
  Serial.println(kalibratie_groen[2]);

  Serial.println("Grijs");
  wacht_op_bevestiging();
  Lijn::lees_waarde();
  kalibratie_grijs[1] = lineSensorValues[1];
  kalibratie_grijs[2] = lineSensorValues[2];
  kalibratie_grijs[3] = lineSensorValues[3];

  Serial.print("SLK: ");
  Serial.print(kalibratie_grijs[0]);
  Serial.print(",");
  Serial.print("SMK: ");
  Serial.print(kalibratie_grijs[1]);
  Serial.print(",");
  Serial.print("SRK: ");
  Serial.println(kalibratie_grijs[2]);

  Serial.println("Zwart");
  wacht_op_bevestiging();
  Lijn::lees_waarde();
  kalibratie_zwart[1] = lineSensorValues[1];
  kalibratie_zwart[2] = lineSensorValues[2];
  kalibratie_zwart[3] = lineSensorValues[3];

  Serial.print("SLK: ");
  Serial.print(kalibratie_zwart[0]);
  Serial.print(",");
  Serial.print("SMK: ");
  Serial.print(kalibratie_zwart[1]);
  Serial.print(",");
  Serial.print("SRK: ");
  Serial.println(kalibratie_zwart[2]);
}

void Lijn::wacht_op_bevestiging() {
  Serial.read();
  while (!Serial.available()) {
    delay(1);
  }
  delay(6000);
  return;
}

bool Lijn::is_binnen_bounds(int& val, int& bound) {
  int max = bound + 50;
  int min = bound = 50;
  if (min < 0) {
    min = 0;
  }
  return (val >= min) && (val <= max);
}

int Lijn::handmatig_kleuren() {
  int links, midden, rechts;
  links = 0;
  midden = 0;
  rechts = 0;
  Lijn::lees_waarde();
  if (lineSensorValues[0] >= 800 && lineSensorValues[0] <= 1500) {
    links = 2;
  } else if (lineSensorValues[0] >= 200 && lineSensorValues[0] <= 220) {
    links = 3;
  } else if (lineSensorValues[0] >= 260 && lineSensorValues[0] <= 280) {
    links = 4;
  } else {
    links = 0;
  }
  if (lineSensorValues[1] >= 800 && lineSensorValues[1] <= 1500) {
    midden = 2;
  } else if (lineSensorValues[1] >= 110 && lineSensorValues[1] <= 130) {
    midden = 1;
  } else {
    midden = 0;
  }
  if (lineSensorValues[2] >= 800 && lineSensorValues[2] <= 1500) {
  } else if (lineSensorValues[2] >= 200 && lineSensorValues[2] <= 220) {
    rechts = 3;
  } else if (lineSensorValues[2] >= 260 && lineSensorValues[2] <= 280) {
    rechts = 4;
  } else {
    rechts = 0;
  }
  return links, midden, rechts;
}

int Lijn::handmatig_kleuren_links() {
  int links;
  if (lineSensorValues[0] >= 800 && lineSensorValues[0] <= 1500) { // ZWART
    links = 2;
  } else if (lineSensorValues[0] >= 140 && lineSensorValues[0] <= 170) { // GRIJS
    links = 3;
  } else if (lineSensorValues[0] >= 290 && lineSensorValues[0] <= 330) { // BRUIN
    links = 4;
  } else {
    links = 0;
  }
  return links;
}

int Lijn::handmatig_kleuren_midden() {
  int midden;
  if (lineSensorValues[1] >= 800 && lineSensorValues[1] <= 1500) { 
    midden = 2;
  } else if (lineSensorValues[1] >= 120 && lineSensorValues[1] <= 180) { // GROEN
    midden = 1;
  } else {
    midden = 0;
  }
  return midden;
}

int Lijn::handmatig_kleuren_rechts() {
  int rechts;
  if (lineSensorValues[2] >= 800 && lineSensorValues[2] <= 1500) {
    rechts = 2;
  } else if (lineSensorValues[2] >= 130 && lineSensorValues[2] <= 170) {
    rechts = 3;
  } else if (lineSensorValues[2] >= 230 && lineSensorValues[2] <= 280) { // BRUIN
    rechts = 4;
  } else {
    rechts = 0;
  }
}

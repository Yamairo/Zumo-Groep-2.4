#include <Wire.h>
#include <Zumo32U4.h>
#include <Zumo32U4LineSensors.h>
#include "lijn.h"


Lijn lijn;

int kleur_links  = 999;
int kleur_midden = 999;
int kleur_rechts = 999;

void setup() {
//  Zumo32U4Motors motors;
  Serial.begin(9600);
  while (!Serial.available()) {
    delay(1);
  }
  lijn.calibrate_test();
  lijn.kalibreer_kleuren();
}


void loop() {
  delay(1000);
  lijn.print_waardes();
  kleur_links, kleur_midden, kleur_rechts = lijn.check_kleur(kleur_links, kleur_midden, kleur_rechts);

  Serial.print("L: ");
  Serial.print(kleur_links);
  Serial.print(" ");

  Serial.print("M: ");
  Serial.print(kleur_midden);
  Serial.print(" ");

  Serial.print("R: ");
  Serial.println(kleur_rechts);
}

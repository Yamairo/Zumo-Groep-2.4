#ifndef LIJNSENSOR
#define LIJNSENSOR

#include <Zumo32U4.h>
#include <Zumo32U4LineSensors.h>
#include <Zumo32U4Motors.h>
#include "Motor.h"

#pragma once

class Lijn {
private:
  Zumo32U4LineSensors lineSensors;
  Zumo32U4Motors motors;
  Motor motor;
  int kalibratie_zwart[3];
  int kalibratie_groen[3];
  int kalibratie_grijs[3];
  int kalibratie_bruin[3];
  void wacht_op_bevestiging();
  bool is_binnen_bounds(int& val, int& bound);

  const int GROEN = 1;
  const int ZWART = 2;
  const int GRIJS = 3;
  const int BRUIN = 4;

public:
  Lijn();
  ~Lijn();
  int lees_waarde();
  void print_waardes();
  int lineSensorValues[3];
  void calibrate_test();
  int check_kleur(int, int, int);
  bool kalibreer_kleuren();
  int handmatig_kleuren();
  int handmatig_kleuren_links();
  int handmatig_kleuren_midden();
  int handmatig_kleuren_rechts();

};
#endif

#ifndef ZUMOGROEP2PUNT4_H
#define ZUMOGROEP2PUNT4_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "Motor.h"
#include "lijn.h"
#include "Xbee.h"

class ZumoGroep2Punt4{
public:
  ZumoGroep2Punt4();
  void init();
  void wisselBesturingsmodus();
  void executeCommand(char command);
private:
  Accelerometer accel;
  Motor motor;
  Magnetometer magnet;
  Lijn Lijn;
  XBee xbee1;
  Zumo32U4Motors motors;
  Zumo32U4ButtonB Knop;
  Zumo32U4ButtonA Automaat;
  Zumo32U4ButtonC Handmatig;
  bool automatisch = false;
  bool buttonPress;
  char command;
};

#endif
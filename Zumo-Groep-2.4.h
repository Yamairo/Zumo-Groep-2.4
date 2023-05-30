#ifndef ZUMOGROEP2PUNT4_H
#define ZUMOGROEP2PUNT4_H

#include <Wire.h>
#include <Zumo32U4.h>
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "Motor.h"
#include "lijn.h"
#include "XBee.h"

class ZumoGroep2Punt4{
public:
  void init();
  void wisselBesturingsmodus();
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
};

#endif
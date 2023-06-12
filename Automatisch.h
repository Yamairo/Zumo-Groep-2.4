#ifndef AUTOMATISCH_H
#define AUTOMATISCH_H

#include "Motor.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "lijn.h"
#include "XBee.h"
#include "Handmatig.h"
#include "prox.h"

class Automatisch {
  public:
    Automatisch();
    ~Automatisch();
    void brugAfrijden();
    void init();
    void duwBlokje();
    void volgLijn();
    Lijn Lijn;
  private:
    Accelerometer accel;
    Handmatig hand;
    Motor motor;
    Magnetometer magnet;
    XBee xbee1;
    ProximitySensors sensors;
    Zumo32U4Motors motors;
    Zumo32U4ButtonB Knop;
    bool buttonPress = Knop.getSingleDebouncedPress();
};

#endif
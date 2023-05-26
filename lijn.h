#ifndef LIJNSENSOR
#define LIJNSENSOR

#include <Zumo32U4.h>
#include <Zumo32U4LineSensors.h>
#include <Zumo32U4Motors.h>
#include "Motor.h"

#pragma once

class lijn
{
  private:
    Zumo32U4LineSensors lineSensors;
    Zumo32U4Motors motors;
    Motor motor;
  public:
    lijn();
    ~lijn();
    int lees_waarde();
    void print_waardes();
    int lineSensorValues[3];
    void calibrate_test();


};
#endif

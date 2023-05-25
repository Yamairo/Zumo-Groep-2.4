#ifndef MOTOR_H
#define MOTOR_H

#include <Zumo32U4.h>
#include <Zumo32U4Motors.h>
#include <Wire.h>

class Motor{
public:
    Motor(); // Constructor declaration
    void test();
    void init();
    void stop();
    void rechteLijn();
private:
    const uint16_t motorspeed = 300;
    Zumo32U4Motors Motor;
    Zumo32U4ButtonA Knop;
    bool buttonPress;
};

#endif

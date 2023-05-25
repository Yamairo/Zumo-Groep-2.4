#include <stdint.h>
#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <Zumo32U4.h>

class Accelerometer {
public:
    Accelerometer();
    ~Accelerometer();
    void sensorenInitialiseren();
    bool brugKantelingDetecteren();
    void snelheidsverschilBerekenen();
    void controleerLinksRechtsBeweging();
    void botsingControleren();

private:
    Zumo32U4IMU imu;
    const int32_t kantelbrugDrempelwaarde = 10;
    const int acceleratieDrempelwaarde = 10;
    const int drempelwaarde = 100;
    const float deltaTijd = 0.4;
    float snelheid = 0.0;
    const float beginsnelheid = 0.0;
    float vorigeAccX;
    float vorigeAccY;
    int delta_a;
    int delta_t;
};

#endif

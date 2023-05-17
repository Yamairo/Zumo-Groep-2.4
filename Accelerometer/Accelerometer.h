#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <Zumo32U4.h>

class Accelerometer {
public:
    Accelerometer();
    void sensorenInitialiseren();
    void brugKantelingDetecteren(void (*functie)(), void (*functie2)());
    void snelheidsverschilBerekenen();
    void controleerLinksRechtsBeweging();
    void botsingControleren();

private:
    Zumo32U4IMU imu;
    const int kantelbrugDrempelwaarde = 3;
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

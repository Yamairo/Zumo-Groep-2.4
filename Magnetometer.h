#ifndef MAG_H
#define MAG_H 

#include <Wire.h>
#include <Zumo32U4.h>

class Magnetometer {
  public:
    magnet();
    void geefWaardes();
    bool check();
    void init();
  private:
    Zumo32U4IMU imu;  
    int x0;
    int y0;
    int z0;
};

#endif

#define PROX_h

#include <Zumo32U4.h>
#include <string.h>

class Prox
{
    {
public:
    //Prox(); // declare constructor
    //int lees_prox(bool calibreer);
    //int ProximitySensorValues[3];
    bool readBasic(uint8_t sensorNumber);
    void read();
    bool readBasicLeft()
     {
         return readBasic(findIndexForPin(SENSOR_LEFT));
     }

     bool readBasicFront()
     {
         return readBasic(findIndexForPin(SENSOR_FRONT));
     }

     bool readBasicRight()
     {
         return readBasic(findIndexForPin(SENSOR_RIGHT));
     }



private:
        Zumo32U4ProximitySensors proximitySensors;
    } 
};


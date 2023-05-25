#define PROX_h

#include <Zumo32U4.h>

class Prox
{
public:
    Prox(); // declare constructor
    int lees_prox();
    int ProximitySensorValues[];

private:
        Zumo32U4ProximitySensors proximitySensors;
        //calibratie
        const int SENSOR_LINKS_OFFSET = 0;
        const int SENSOR_MIDDEN_OFFSET = 0;
        const int SENSOR_RECHTS_OFFSET = 0;
}
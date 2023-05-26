#include "prox.h"
#include <Zumo32U4.h>

Prox::Prox() {
    proximitySensors.initThreeSensors();
}

//leest sensoren uit 
int Prox::lees_prox(bool calibreer){
    proximitySensors.read();
    if (calibreer){
        ProximitySensorValues[0] = ProximitySensorValues[0] + SENSOR_LINKS_OFFSET;
        ProximitySensorValues[1] = ProximitySensorValues[1] + SENSOR_MIDDEN_OFFSET;
        ProximitySensorValues[2] = ProximitySensorValues[2] + SENSOR_RECHTS_OFFSET;
    }
    return ProximitySensorValues;
}
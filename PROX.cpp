#include "PROX.h"
#include <Zumo32U4.h>

prox::prox() {
    ProximitySensors.initThreeSensors();
}

//leest sensoren uit 
int prox::lees_prox(){
    ProximitySensors.read(ProximitySensorValues);
    if (calibreer){
        ProximitySensorValues[0] = ProximitySensorValues[0] + SENSOR_LINKS_OFFSET;
        ProximitySensorValues[1] = ProximitySensorValues[1] + SENSOR_MIDDEN_OFFSET;
        ProximitySensorValues[2] = ProximitySensorValues[2] + SENSOR_RECHTS_OFFSET;
    }
    return ProximitySensorValues;
}
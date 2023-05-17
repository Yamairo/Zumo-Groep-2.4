#include <Zumo32U4.h>
class lijn
{
private:
        Zumo32U4LineSensors lineSensors;
        // TODO: Offsets invullen
        const int SENSOR_LINKS_OFFSET  = 0;
        const int SENSOR_RECHTS_OFFSET = 0;
        const int SENSOR_MIDDEN_OFFSET = 0;
public:
    lijn();
    ~lijn();
    int lees_waarde(bool kalibreer);
    void print_ruwe_waardes();
    int lineSensorValues[3];

};

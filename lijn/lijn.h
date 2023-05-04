#include <Zumo32U4.h>
class lijn
{
private:
        Zumo32U4LineSensors lineSensors;
public:
    lijn();
    ~lijn();
    int lees_waarde();
    void print_waardes();
    int lineSensorValues[3];

};

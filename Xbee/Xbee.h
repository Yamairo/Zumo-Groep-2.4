#include <Zumo32U4Motors.h>
#ifndef XBEE_H
#define XBEE_H
using namespace std;
/*!Header file*/
class XBee {
public:
    XBee();
    ~XBee();
    void begin(int b);
    void send(String d);
    String receive();
    void startMotorsOnKeyPress(Zumo32U4Motors);
};

#endif

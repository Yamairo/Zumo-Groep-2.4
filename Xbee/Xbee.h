#ifndef XBEE_H
#define XBEE_H
using namespace std;
/*!Header file*/
class XBee {
public:
    XBee();
    ~XBee();
    void begin(int);
    void send(String);
    char receive();
    // void startMotorsOnKeyPress(Zumo32U4Motors);
private:
String data;
int baud;
char c;
};

#endif
 
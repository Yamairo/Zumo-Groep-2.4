#ifndef XBEE_H
#define XBEE_H
using namespace std;
/*!Header file*/
class XBee {
public:
    XBee();
    ~XBee();
    void begin(int);
    void send(char);
    char receive();
    // void startMotorsOnKeyPress(Zumo32U4Motors);
private:
char data;
int baud;
char c;
};

#endif
 
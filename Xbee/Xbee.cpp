#include "WString.h"
#include "Xbee.h"
#include <Wire.h>
#include <Zumo32U4Motors.h>
//#include <SoftwareSerial.h>


using namespace std;
/*!cpp file*/
SoftwareSerial xbee(2, 3);

/*!constructor*/
XBee::XBee() {}

/*!deconstructor*/
XBee::~XBee(){}

/*!begint met de gegeven baud*/
void XBee::begin(int baud) {
    xbee.begin(baud);
}

/*!stuurt data naar de Xbee*/
void XBee::send(String data) {
    xbee.println(data);
}

String XBee::receive(){
  String data = "";
  while(xbee.available()){
    char c = xbee.read();
    data += c;
  }
  return data;
}

void XBee::startMotorsOnKeyPress(Zumo32U4Motors motors) {

  
  
    while (true) {
        if (xbee.available()) {
            char c = xbee.read();
            if (c == 'w') {
                /*Rechtdoor*/
                motors.setLeftSpeed(200);
                motors.setRightSpeed(200);
            }
            if (c == 's'){
                /*acheruit*/
                motors.setLeftSpeed(-200);
                motors.setRightSpeed(-200);
            }
            if (c == 'a'){
                /*zumo naar links*/
                motors.setLeftSpeed(-100);
                motors.setRightSpeed(100);
            }
            if (c == 'd'){
                /*zumo naar rechts*/
                motors.setLeftSpeed(100);
                motors.setRightSpeed(-100);
            }
                
                
            
        }
    }
}
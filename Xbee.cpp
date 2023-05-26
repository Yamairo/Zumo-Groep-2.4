#include "HardwareSerial.h"
#include "WString.h"
#include "Xbee.h"
#include <Wire.h>
// #include <SoftwareSerial.h>

// SoftwareSerial xbee(2, 3);

using namespace std;
/*!cpp file*/

/*!constructor*/
XBee::XBee() {}

/*!deconstructor*/
XBee::~XBee(){}

/*!begint met de gegeven baud*/
void XBee::begin(int baud) {
    Serial1.begin(baud);
}

/*!stuurt data naar de Xbee*/
void XBee::send(char data) {
    Serial1.println(data);
}

char XBee::receive(){
  char inkomend = 0;
  if(Serial1.available()>0){
    inkomend = Serial1.read();
    Serial1.println(inkomend);
    
  }
  return inkomend;
}



#include "Xbee.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Zumo32U4Motors.h>

using namespace std;

XBee xbee1;
Zumo32U4Motors motor;

/*!test file */
void setup() {
  xbee1.begin(9600);
}

void loop() {
  
  /*!stuurt data*/
  // xbee1.send("Test 123");
  // delay(100);
  // xbee1.send(xbee1.receive());
  delay(100);
  xbee1.startMotorsOnKeyPress(motor);
}

#include "Xbee.h"
#include <Wire.h>
#include "Keyboard.h"

// #include <Zumo32U4Buttons.h>

using namespace std;

// Zumo32U4ButtonA buttonA;
XBee xbee1;

/*!test file */
void setup() {
  Serial1.begin(9600);
}

void loop() {

  /*!stuurt data*/
  // xbee1.send("Test123");
  delay(200);
  xbee1.receive();



}
#include <Wire.h>
#include <Zumo32U4.h>
#include "prox.h"

ProximitySensors sensors;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  sensors.read();
  uint16_t left = sensors.getLeft();
  uint16_t right = sensors.getRight();
  uint16_t middle = sensors.getMiddle();

  Serial.print("Left: ");
  Serial.print(left);
  Serial.print(", Right: ");
  Serial.print(right);
  Serial.print(", Middle: ");
  Serial.println(middle);

  delay(100);
}

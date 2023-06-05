#include <Wire.h>
#include <Zumo32U4.h>
#include "prox.h"

ProximitySensors prox;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  prox.read();

  uint16_t left = prox.getLeft();
  uint16_t right = prox.getRight();
  uint16_t front = prox.getFront();

  Serial.print("Left: ");
  Serial.print(left);
  Serial.print("\tRight: ");
  Serial.print(right);
  Serial.print("\tFront: ");
  Serial.println(front);

  delay(100);
}

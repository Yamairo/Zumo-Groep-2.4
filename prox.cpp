#include <Wire.h>
#include <Zumo32U4.h>
#include "prox.h"

ProximitySensors::ProximitySensors()
{
  Wire.begin();
  sensors.initThreeSensors();
}

void ProximitySensors::read()
{
  sensors.read();
}

uint16_t ProximitySensors::getLeft() const
{
  return sensors.countsFrontWithLeftLeds();
}

uint16_t ProximitySensors::getRight() const
{
  return sensors.countsFrontWithRightLeds();
}

uint16_t ProximitySensors::getMiddle() const
{
  return sensors.countsFrontWithLeftLeds() + sensors.countsFrontWithRightLeds();
}

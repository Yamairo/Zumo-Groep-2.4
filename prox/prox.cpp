#include <Wire.h>
#include <Zumo32U4.h>

// Initialize proximity sensors
ProximitySensors::ProximitySensors()
{
  Wire.begin();
  sensors.initThreeSensors();
}

// Read proximity sensor values
void ProximitySensors::read()
{
  sensors.read();
}

// Get value of left proximity sensor
uint16_t ProximitySensors::getLeft() const
{
  return sensors.countsFrontWithLeftLeds();
}

// Get value of right proximity sensor
uint16_t ProximitySensors::getRight() const
{
  return sensors.countsFrontWithRightLeds();
}

// Get sum of both proximity sensors' values
uint16_t ProximitySensors::getMiddle() const
{
  return sensors.countsFrontWithLeftLeds() + sensors.countsFrontWithRightLeds();
}

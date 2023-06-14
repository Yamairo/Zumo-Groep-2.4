
#include <Wire.h>
#include <Zumo32U4.h>


class ProximitySensors {
 public:
  /**
   * @brief Constructor.
   */
  ProximitySensors();

  /**
   * @brief Reads proximity sensor values.
   */
  void read();

  /**
   * @brief Gets value of left proximity sensor.
   * @return Value of left proximity sensor.
   */
  uint16_t getLeft() const;

  /**
   * @brief Gets value of right proximity sensor.
   * @return Value of right proximity sensor.
   */
  uint16_t getRight() const;

  /**
   * @brief Gets sum of both proximity sensors' values.
   * @return Sum of both proximity sensors' values.
   */
  uint16_t getMiddle() const;

 private:
  Zumo32U4ProximitySensors sensors; /**< Proximity sensors. */
};

/**
 * @brief Constructor.
 */
ProximitySensors::ProximitySensors()
{
  Wire.begin();
  sensors.initThreeSensors();
}

/**
 * @brief Reads proximity sensor values.
 */
void ProximitySensors::read()
{
  sensors.read();
}

/**
 * @brief Gets value of left proximity sensor.
 * @return Value of left proximity sensor.
 */
uint16_t ProximitySensors::getLeft() const
{
  return sensors.countsFrontWithLeftLeds();
}

/**
 * @brief Gets value of right proximity sensor.
 * @return Value of right proximity sensor.
 */
uint16_t ProximitySensors::getRight() const
{
  return sensors.countsFrontWithRightLeds();
}

/**
 * @brief Gets sum of both proximity sensors' values.
 * @return Sum of both proximity sensors' values.
 */
uint16_t ProximitySensors::getMiddle() const
{
  return sensors.countsFrontWithLeftLeds() + sensors.countsFrontWithRightLeds();
}



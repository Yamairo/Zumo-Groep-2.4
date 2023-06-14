#ifndef PROX_H
#define PROX_H

#include <Wire.h>
#include <Zumo32U4.h>

class ProximitySensors
{
  public:
    ProximitySensors();
    void read();
    uint16_t getLeft() const;
    uint16_t getRight() const;
    uint16_t getMiddle() const;

  private:
    Zumo32U4ProximitySensors sensors;
};

#endif
#include "Motor.h"
#include "Handmatig.h"

Handmatig::Handmatig(){

}

Handmatig::~Handmatig(){

}

void Handmatig::HandmatigeBesturing(char input) {
  /*!
   * \brief Geeft de besturings commandos door.
   *
   * Door het sturen van "W", "A", "S", "D", "X" kan je de zumo besturen
   * hiebij is W vooruit; A linksom draaien; S achteruit rijden; D rechtsom draaien;
   * X voor het stoppen van de motoren.
   */
  switch (input) {
    case 'W':
      motor.rijVooruit();
      break;
    case 'A':
      motor.draaiLinks();
      break;
    case 'S':
      motor.rijAchteruit();
      break;
    case 'D':
      motor.draaiRechts();
      break;
    case 'X':
      motor.stopMotors();
      break;
    default:
      break;
  }
}
#include "USBAPI.h"
#include "WString.h"
/*!
 * \file Accelerometer.cpp
 * \brief Bevat de implementatie van de functies van de klas Accelerometer.
 * \author [Yamairo Martinus]
 * \date [5-5-2023]
 */

/*!
 * \mainpage Accelerometer Klasse Documentatie
 *
 * \section intro_sec Inleiding
 *
 * Deze documentatie beschrijft functionaliteit van de C++ klasse Accelerometer. Deze klasse bevat functies om de sensoren van de Zumo-robot te initialiseren en het verschil in acceleratie te meten om de snelheid te bepalen. De klasse bevat ook een functie om een melding te geven als de snelheid plots naar 0 gaat, wat kan duiden op een botsing of crash.
 *
 * \section installatie_sec Installatie
 *
 * Deze klas is bedacht op bassis van de Zumo libraries daarom is het van belang dat je de volgende libraries hebt:
 * - Wire.h
 * - Zumo32U4.h
 *
 * \section gebruik_sec Gebruik
 *
 * Om deze klasse te gebruiken, moet u eerst een object van de klasse aanmaken.
 *
 * Voor meer gedetailleerde informatie over de functies van de klasse, zie de documentatie van de individuele functies.
 */


#include "Accelerometer.h"

Accelerometer::Accelerometer() {}

void Accelerometer::sensorenInitialiseren() {
  /*!
   * \brief Initialiseert de sensoren en geeft een melding als dit niet lukt.
   *
   * Deze functie initialiseert de sensoren en geeft een melding als dit niet lukt.
   * Als de sensoren niet gedetecteerd worden, wordt de rode LED op de Zumo-robot
   * ingeschakeld en wordt er een bericht op de seriële monitor geprint.
   */
  Serial.begin(9600);
  Wire.begin();
  imu.init();
  if (!imu.init())
  {
    ledRed(1);
    while(1)
    {
      Serial.println(("De initialisatie van de sensoren is mislukt"));
      delay(100);
    }
  }
  imu.enableDefault();
}

void Accelerometer::brugKantelingDetecteren(void (*functie)(), void (*functie2)()) {
  /*!
   * \brief Detecteert een kantelbrug op basis van de helling van de robot.
   *
   * Deze functie gebruikt de accelerometergegevens om de helling van de robot te detecteren.
   * Als de helling groter is dan een drempelwaarde, wordt aangenomen dat de robot een kantelbrug nadert.
   * Op basis van deze detectie kunt u de snelheid aanpassen, de rijrichting wijzigen of andere relevante acties ondernemen.
   */

  imu.readAcc();
  int acc_x = imu.a.x;
  int acc_z = imu.a.z;

  // Bereken de helling in graden
  float helling = atan2(acc_x, acc_z) * 180.0 / PI;

  // Controleer of de helling groter is dan de drempelwaarde voor kantelbrug
  if ((helling) > kantelbrugDrempelwaarde) {
    // Voer de gewenste acties uit voor kantelbrug detectie
    functie();
  }
  else if ((helling) < -kantelbrugDrempelwaarde) {
    // Voer de gewenste acties uit voor kantelbrug detectie
    functie2();
  }
}


void Accelerometer::snelheidsverschilBerekenen() {
  /*!
   * \brief Bereken de daadwerkelijke snelheid op basis van het verschil in acceleratie en tijd.
   *
   * Deze functie leest de waarde van de acceleratie op twee momenten en berekent de snelheid
   * op basis van de verandering in acceleratie en de opgegeven tijdsinterval (delta t). De snelheid
   * wordt bijgewerkt door de integratie van de veranderingen in acceleratie en geprint op de seriële monitor.
   */

  imu.readAcc();
  int acc_x_1 = imu.a.x;
  delay(400);   
  imu.readAcc();
  int acc_x_2 = imu.a.x;
  int delta_a = acc_x_2 - acc_x_1;

  float snelheid = beginsnelheid; // Beginsnelheid

  while (!(abs(delta_a) < drempelwaarde)) {
    imu.readAcc();
    int acc_x_prev = acc_x_2;
    acc_x_2 = imu.a.x;
    delta_a = acc_x_2 - acc_x_prev;

    // Voeg het teken van delta_a toe aan de snelheid
    if (delta_a > 0) {
      snelheid += delta_a * delta_t; // Verhoog de snelheid bij acceleratie
    } else if (delta_a < 0) {
      snelheid += delta_a * delta_t; // Verlaag de snelheid bij vertraging
    }
    Serial.println(snelheid);
    Serial.println("snelheid=" + String(snelheid));
  }
}


void Accelerometer::botsingControleren() {
  /*!
   * \brief Geeft een melding als de snelheid plots naar 0 gaat.
   *
   * Deze functie geeft een melding als de snelheid plots naar 0 gaat, wat kan duiden op een
   * botsing of crash. Het bericht "Ouch, dat deed pijn" wordt geprint op de seriële monitor.
   */
  if (snelheid == 0){
    Serial.println("Ouch, dat deed pijn");
  }
}

void Accelerometer::controleerLinksRechtsBeweging() {
    /*!
    * \brief Controleert de links-rechtsbeweging van de Zumo-robot op basis van de acceleratiewaarden.
    *
    * Deze functie controleert de links-rechtsbeweging van de Zumo-robot op basis van de acceleratiewaarden.
    * Als de robot in de y-richting beweegt, wordt gecontroleerd op veranderingen in de x-richting en vice versa.
    * Pas de drempelwaarden aan om de gevoeligheid van de bewegingsdetectie aan te passen.
    */
    // Lees de acceleratiewaarden
    imu.readAcc();
    float accX = imu.a.x;
    float accY = imu.a.y;

    // Controleer de links-rechtsbeweging op basis van de acceleratie
    if (abs(accY) > drempelwaarde) {
        // Beweeg in de y-richting, controleer de x-richting
        if (accX > drempelwaarde) {
            // Beweeg naar rechts
            // Voer hier uw acties uit
            Serial.print("Je beweegt naar rechts");
        } else if (accX < -drempelwaarde) {
            // Beweeg naar links
            // Voer hier uw acties uit
            Serial.print("Je beweegt naar links");
        }
    } else if (abs(accX) > drempelwaarde) {
        // Beweeg in de x-richting, controleer de y-richting
        if (accY > drempelwaarde) {
            // Beweeg naar voren
            // Voer hier uw acties uit
            Serial.print("Je beweegt naar rechts2");

        } else if (accY < -drempelwaarde) {
            // Beweeg naar achteren
            // Voer hier uw acties uit
            Serial.print("Je beweegt naar links2");

        }
    }
    // Bewaar de huidige acceleratiewaarden voor de volgende iteratie
    vorigeAccX = accX;
    vorigeAccY = accY;
}

#include "Accelerometer.h"

Accelerometer::Accelerometer() {}
Accelerometer::~Accelerometer() {}

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
    Serial.print("Kaas");
  }
  imu.enableDefault();
}

bool Accelerometer::brugKantelingDetecteren() {
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
  float helling1 = atan2(acc_x, acc_z) * 180.0 / PI;
  delay(20);
  imu.readAcc();
  acc_x = imu.a.x;
  acc_z = imu.a.z;

  // Bereken de helling in graden
  float helling2 = atan2(acc_x, acc_z) * 180.0 / PI;
  
  float helling = (helling1 + helling2)/2;
  // Controleer of de helling groter is dan de drempelwaarde voor kantelbrug
  if ((helling) > kantelbrugDrempelwaarde) {
    // Voer de gewenste acties uit voor kantelbrug detectie
    Serial.println("Hel op");
    return true;
  }
  else{
    // Voer de gewenste acties uit voor kantelbrug detectie
    Serial.println("Helling Af");
    return false;
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

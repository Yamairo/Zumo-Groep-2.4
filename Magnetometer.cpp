/*!
Dit voorbeeld leest de waarden van de magnetometer op de ZUMO 32U4,
en print deze waarden op de seriele monitor.

Voor de kalibratie worden eerst de beginwaarden gemeten en vastgesteld,
om daarna deze waarden van de eindwaarden af te trekken.
Matis Keita, 05-05-2023
*/

#include "Magnetometer.h"

char report[120];



// --- Setup function
void Magnetometer::init() {
  /*
  */

  Wire.begin();

  //imu initialiseren
  if (!imu.init()) {

    // Kompas werdt niet gedetecteerd.
    ledRed(1);      // rode led aan
    while (true) {  // loop blijft aan
      Serial.println(F("Failed to initialize IMU sensors."));
      delay(100);
    }
  }

  imu.enableDefault();

  // Kalibreren:
  // Begin waarden lezen en vaststellen.
  /*Serial.println(F("Calibration..."));

  while (!imu.magDataReady())
  {
    delay(100);
  }

  imu.readMag();

  x0 = imu.m.x;
  y0 = imu.m.y;
  z0 = imu.m.z;

  Serial.println(F("Done"));
  */
}

bool Magnetometer::check() {
  /*
  */
  // Wacht tot dat magData beschikbaar is, anders wacht 100 ms.
  while (!imu.magDataReady()) {
    delay(100);
    return true;
  }
}

// --- Main program loop
void Magnetometer::geefWaardes() {
  /*!

  */
  if (check()) {
    // Meet magData
    imu.readMag();

    // Weergeeft de data op de serialdisplay.
    snprintf_P(report, sizeof(report),
               PSTR("M: %6d %6d %6d"),
               imu.m.x, imu.m.y, imu.m.z);  // imu.m.x - x0, imu.m.y - y0, imu.m.z - z0 als de kalibratie gebruikt wordt.
    Serial.println(report);
  }
  delay(1000);
}

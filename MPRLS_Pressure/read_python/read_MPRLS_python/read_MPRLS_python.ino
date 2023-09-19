/*!
 * @file mprls_simpletest.ino
 *
 * A basic test of the sensor with default settings
 * 
 * Designed specifically to work with the MPRLS sensor from Adafruit
 * ----> https://www.adafruit.com/products/3965
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.  
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */
 
#include <Wire.h>
#include "Adafruit_MPRLS.h"

// You dont *need* a reset and EOC pin for most uses, so we set to -1 and don't connect
#define RESET_PIN  -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN    -1  // set to any GPIO pin to read end-of-conversion by pin
Adafruit_MPRLS mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

const int HANDSHAKE = 0;
const int PRESS_REQUEST = 1;

int inByte;

void printPress() {
  float pressure_hPa = mpr.readPressure();
  //Serial.print("Pressure (hPa): "); Serial.println(pressure_hPa);
  //Serial.print("Pressure (PSI): "); Serial.println(pressure_hPa / 68.947572932);
  //Serial.println(pressure_hPa);
  // Write the result
  if (Serial.availableForWrite()) {
    Serial.println(String(pressure_hPa, DEC)); // DEC 
  }
}



void setup() {
  Serial.begin(115200);
  //Serial.println("MPRLS Simple Test");
  mpr.begin();
  //if (! mpr.begin()) {
  //  Serial.println("Failed to communicate with MPRLS sensor, check wiring?");
  //  while (1) {
  //    delay(10);
  //  }
  //}
  //Serial.println("Found MPRLS sensor");
}


void loop() {
  //float pressure_hPa = mpr.readPressure();
  //Serial.print("Pressure (hPa): "); Serial.println(pressure_hPa);
  //Serial.print("Pressure (PSI): "); Serial.println(pressure_hPa / 68.947572932);
  //Serial.println(pressure_hPa);
  //delay(1000);
  // Check if data has been sent to Arduino and respond accordingly
  if (Serial.available() > 0) {
    // Read in request
    inByte = Serial.read();

    // If data is requested, fetch it and write it, or handshake
    switch(inByte) {
      case PRESS_REQUEST:
        printPress();
        break;
      case HANDSHAKE:
        if (Serial.availableForWrite()) {
          Serial.println("Message received.");
        }
        break;
    }
  }
}

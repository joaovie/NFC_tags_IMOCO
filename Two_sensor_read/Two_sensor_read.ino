#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_MPRLS.h"


//MPRLS
#define RESET_PIN  -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN    -1  // set to any GPIO pin to read end-of-conversion by pin
Adafruit_MPRLS mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

//MS9607
Adafruit_MS8607 ms8607;


void setup(void) {
  Serial.begin(115200);
  Serial.println("Start setup sensors");

  //Search for MPRLS sensor
  if (! mpr.begin()) {
      Serial.println("Failed to communicate with MPRLS sensor, check wiring?");
      while (1) {
        delay(10);
      }
    }
    Serial.println("Found MPRLS sensor");
  
  //Search for MS8607 sensor
  if (!ms8607.begin()) {
    Serial.println("Failed to find MS8607 chip");
    while (1) { delay(10); }
  }
  Serial.println("MS8607 Found!");
  ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);

}

void loop() {
    //MPRLS
    float pressure_hPa = mpr.readPressure();
    Serial.println("MPRLS");
    Serial.print("Pressure (hPa): "); Serial.println(pressure_hPa);
    Serial.print("Pressure (PSI): "); Serial.println(pressure_hPa / 68.947572932);
    delay(1000);

    //MS8607
    sensors_event_t temp, pressure, humidity;
    ms8607.getEvent(&pressure, &temp, &humidity);

    Serial.println("MS8607");
    Serial.print("Temperature: ");Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Pressure: ");Serial.print(pressure.pressure); Serial.println(" hPa");
    Serial.print("Humidity: ");Serial.print(humidity.relative_humidity); Serial.println(" %rH");
    Serial.println("");
    delay(500);  

}

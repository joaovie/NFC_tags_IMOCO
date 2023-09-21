// Basic demo for reading Humidity and Temperature
#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>

const int HANDSHAKE = 0;
const int MEASURE_REQUEST = 1;

int inByte;

Adafruit_MS8607 ms8607;

void printMeasure() {
  sensors_event_t temp, pressure, humidity;
  ms8607.getEvent(&pressure, &temp, &humidity);
  //Serial.print("Pressure (hPa): "); Serial.println(pressure_hPa);
  //Serial.print("Pressure (PSI): "); Serial.println(pressure_hPa / 68.947572932);
  //Serial.println(pressure_hPa);
  // Write the result
  if (Serial.availableForWrite()) {
    //Serial.println(String(pressure_hPa, DEC)); // DEC
    Serial.print(temp.temperature);
    Serial.print(" "); 
    Serial.print(pressure.pressure);//hPa
    Serial.print(" ");
    Serial.println(humidity.relative_humidity);

  }
}

void setup(void) {
  Serial.begin(115200);
  ms8607.begin();
  ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);
  ms8607.setPressureResolution(MS8607_PRESSURE_RESOLUTION_OSR_4096);

  //while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  //Serial.println("Adafruit MS8607 test!");

  // Try to initialize!
  //if (!ms8607.begin()) {
  //  Serial.println("Failed to find MS8607 chip");
  //  while (1) { delay(10); }
  //}
  //Serial.println("MS8607 Found!");

  //ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);
  //Serial.print("Humidity resolution set to ");
  //switch (ms8607.getHumidityResolution()){
  //  case MS8607_HUMIDITY_RESOLUTION_OSR_12b: Serial.println("12-bit"); break;
  //  case MS8607_HUMIDITY_RESOLUTION_OSR_11b: Serial.println("11-bit"); break;
  //  case MS8607_HUMIDITY_RESOLUTION_OSR_10b: Serial.println("10-bit"); break;
  //  case MS8607_HUMIDITY_RESOLUTION_OSR_8b: Serial.println("8-bit"); break;
  //}
  //ms8607.setPressureResolution(MS8607_PRESSURE_RESOLUTION_OSR_4096);
  //Serial.print("Pressure and Temperature resolution set to ");
  //switch (ms8607.getPressureResolution()){
  //  case MS8607_PRESSURE_RESOLUTION_OSR_256:  Serial.println("256"); break;
  //  case MS8607_PRESSURE_RESOLUTION_OSR_512:  Serial.println("512"); break;
  //  case MS8607_PRESSURE_RESOLUTION_OSR_1024: Serial.println("1024"); break;
  //  case MS8607_PRESSURE_RESOLUTION_OSR_2048: Serial.println("2048"); break;
  //  case MS8607_PRESSURE_RESOLUTION_OSR_4096: Serial.println("4096"); break;
  //  case MS8607_PRESSURE_RESOLUTION_OSR_8192: Serial.println("8192"); break;
  //}
  //Serial.println("");
}

void loop() {
  if (Serial.available() > 0) {
    // Read in request
    inByte = Serial.read();

    // If data is requested, fetch it and write it, or handshake
    switch(inByte) {
      case MEASURE_REQUEST:
        printMeasure();
        break;
      case HANDSHAKE:
        if (Serial.availableForWrite()) {
          Serial.println("Message received.");
        }
        break;
    }
  }
    //sensors_event_t temp, pressure, humidity;
    //ms8607.getEvent(&pressure, &temp, &humidity);
    //Serial.print("Temperature: ");Serial.print(temp.temperature); Serial.println(" degrees C");
    //Serial.print("Pressure: ");Serial.print(pressure.pressure); Serial.println(" hPa");
    //Serial.print("Humidity: ");Serial.print(humidity.relative_humidity); Serial.println(" %rH");
    //Serial.println("");

    //Serial.print(temp.temperature);
    //Serial.print(" ");
    //Serial.println(pressure.pressure*0.1);//kPa
    //delay(500);
}

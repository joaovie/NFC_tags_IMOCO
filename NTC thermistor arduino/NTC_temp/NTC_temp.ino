/*
  Arduino NTC thermistor read

  This Arduino program reads the temperature value from a Semitec TX04F103F3380ER NTC thermistor
  using a voltage divider circuit with a 10k reference resistor. The 5V supply is provided from a
  digital pin to avoid self-heating phenomena. 
  The program takes 5 samples and calculates the average for better accuracy.

  Thermistor: Semitec TX04F103F3380ER
  Beta: 3380 K
  Nominal temperature: 25 °C
  Nominal Resistance: 10 kΩ
  Reference Resistor: 10 kΩ
  Analog Pin: Replace 'A0' with the analog pin connected to the voltage divider output
  Supply Pin: Replace '2' with the digital pin number supplying 5V to the voltage divider circuit

  Formula for calculating thermistor resistance:
  thermistorResistance = referenceResistor / ((1023.0 / analogValue - 1.0))

  Steinhart-Hart equation:
  temperature = (1/To) + 1/B * ln(R/Ro)   //Kelvin
  temperatureCelsius = temperature - 273.15

  Written by João Vieira
  Date: 27/07/2023
*/
#define ntc_pin A0                 // Pin to which the voltage divider is connected
#define vd_power_pin 2             // 5V for the voltage divider
#define nominal_resistance 10000   // Nominal resistance at 25⁰C
#define nominal_temperature 25     // Temperature for nominal resistance (almost always 25⁰ C)
#define samplingrate 5             // Number of samples
#define beta 3380                  // The beta coefficient or the B value of the thermistor (usually 3000-4000) check the datasheet for the accurate value.
#define Rref 10000                 // Value of  resistor used for the voltage dividerint samples = 0;   //array to store the samples
int samples = 0;                   // Array to store the samples
void setup(void) {
  pinMode(vd_power_pin, OUTPUT);
  pinMode(ntc_pin, INPUT);
  Serial.begin(9600);   //initialize serial communication at a baud rate of 9600
}

void loop(void) {
  uint8_t i;
  float average;
  samples = 0;
  // take voltage readings from the voltage divider
  digitalWrite(vd_power_pin, HIGH);
  for (i = 0; i < samplingrate; i++) {
    samples += analogRead(ntc_pin);
    delay(10);
  }
  digitalWrite(vd_power_pin, LOW);
  average = 0;
  average = samples / samplingrate;
  Serial.println("\n \n");
  Serial.print("ADC readings ");
  Serial.println(average);

  // Calculate NTC resistance
  average = 1023 / average - 1;
  average = Rref / average;
  Serial.print("Thermistor resistance ");
  Serial.println(average);

  float temperature;
  temperature = average / nominal_resistance;     // (R/Ro)
  temperature = log(temperature);                  // ln(R/Ro)
  temperature /= beta;                   // 1/B * ln(R/Ro)
  temperature += 1.0 / (nominal_temperature + 273.15); // + (1/To)
  temperature = 1.0 / temperature;                 // Invert
  temperature -= 273.15;                         // convert absolute temp to C

  Serial.print("Temperature ");
  Serial.print(temperature);
  Serial.println(" *C");

  delay(2000);
}
#include "shared/dependencies.h"

double calculate_resistance();
double steinhart();

double calculate_resistance()
{
  double resistor = 0;
  uint16_t adcRaw = 0;
  double adcVoltage = 0;

  for (int i = 0; i < 3; i++)
    adcRaw = +analogReadMilliVolts(0);
  Serial.printf("Raw ADC: %d \n", adcRaw);
  adcVoltage = 3.3 * adcRaw / 1024;
  resistor = (3.3 / (adcVoltage)) * PULLDOWN_RES - PULLDOWN_RES;
  if (resistor < 10)
    resistor = 10;
  if (resistor > 140000)
    resistor = 140000;
  return resistor;
}

double steinhart(double thermistor)
{

  //  NTC 3950 10k
  //  const static double  a = 0.0011260101763638105;
  //  const static double  b = 0.00023990205585764816;
  //  const static double  c = -3.1848655700239605e-8;

  //  NTC 3950 100k
  const static double a = 0.0008002314855002526;
  const static double b = 0.0001989545566222665;
  const static double c = 1.7249962319615102e-7;

  // Utilizes the Steinhart-Hart Thermistor Equation:
  // Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  double ln_r = log(thermistor);                                                  // Saving the Log(resistance) so not to calculate it 4 times later.
  float temperature = (1 / (a + (b * ln_r) + (c * ln_r * ln_r * ln_r))) - 273.15; // Convert K to ºC
  return (temperature);
}
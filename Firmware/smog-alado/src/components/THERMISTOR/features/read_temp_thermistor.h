#if !defined(READ_TEMPERATURE_THERMISTOR)
#define READ_TEMPERATURE_THERMISTOR

#include "components/ADS1115/setup.h"

double calculate_resistance()
{
  double resistor = 0;
  uint16_t adcRaw = 0;
  double adcVoltage = 0;
  if (workingADS)
  {
    adcRaw = ads.readADC_SingleEnded(0);
    adcVoltage = ads.computeVolts(adcRaw);
  }
  else
  {
    adcRaw = analogRead(A0);
    adcVoltage = adcRaw / 1024;
  }
  if (adcRaw < 1000)
    return 120000;
  else
    resistor = (3.3 / (adcVoltage)) * PULLDOWN - PULLDOWN;
  if (resistor < 150)
    resistor = 150;
  if (resistor > 120000)
    resistor = 120000;
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

#endif // READ_TEMPERATURE_THERMISTOR

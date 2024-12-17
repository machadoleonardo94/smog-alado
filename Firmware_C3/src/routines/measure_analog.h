#include "shared/dependencies.h"

#ifndef MEASURE_SERVICE
#define MEASURE_SERVICE

double calculate_resistance();
double steinhart();
double calculate_battery();
double calculate_current();
double calculate_load();

double calculate_resistance(int channel, int pulldown)
{
  uint16_t adcRaw = 0;
  double adcVoltage = 0;
  double resistor = 0;

  if (workingADS)
    adcRaw = ads.readADC_SingleEnded(channel); // Channels TH0 and TH1 are valid with ADS
  else
  {
    for (int i = 0; i < 3; i++)
      adcRaw = +analogReadMilliVolts(0); // Only reads TH0 without ADS
  }
  Serial.printf("Raw ADC: %d \n", adcRaw);
  adcVoltage = ads.computeVolts(adcRaw);
  Serial.printf("Voltage at pin: %dV \n", adcRaw);
  resistor = (3.3 / (adcVoltage)) * pulldown - pulldown;
  // resistor = roundl(resistor * 10) / 10;
  resistor = constrain(resistor, 10, 140000);
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

double calculate_battery()
{
  uint16_t adcRaw = 0;
  if (workingADS)
    adcRaw = ads.readADC_SingleEnded(VBATT);
  else
  {
    for (int i = 0; i < 4; i++)
      adcRaw += analogReadMilliVolts(1);
  }
  Serial.printf("Raw reading: %d \n", adcRaw);
  double voltage = ads.computeVolts(adcRaw);
  voltage = voltage * 1.303; // Voltage divider 33k+10k
  // voltage = roundl(voltage * 10) / 10;
  return voltage;
}

double calculate_current()
{
  uint16_t adcRaw = 0;
  if (!workingADS)
    return 0;
  adcRaw = ads.readADC_SingleEnded(Rsns);
  Serial.printf("Raw reading: %d \n", adcRaw);
  double isense = ads.computeVolts(adcRaw);
  // isense = roundl(isense * 10) / 10;
  isense = isense * 2.5; // Rsns 20mR, INA180 gain 20x
  isense = constrain(isense, 0, 20);
  return isense;
}

double calculate_load()
{
  if (!workingADS)
    return 0;
  double resistance = 0;
  // ledcWrite(heater, 1000);
  digitalWrite(heater, HIGH);
  //* Direct method: Apply DC and measure V and I after settling time
  delay(100);
  uint16_t rawBatt = ads.readADC_SingleEnded(VBATT);
  inputVoltage = ads.computeVolts(rawBatt);
  delay(10);
  uint16_t rawSns = ads.readADC_SingleEnded(Rsns);
  double loadCurrent = ads.computeVolts(rawSns) * 2.5; // Compensate gain as I = V(Rsns)/(20*20mR)
  if (loadCurrent > 0.05)
  {
    resistance = inputVoltage / loadCurrent;
    current = loadCurrent;
  }
  // inputVoltage= calculate_battery();
  // current = calculate_current();
  //  if (current > 0.05)
  //  resistance = inputVoltage/ current;
  else
    resistance = 99;
  digitalWrite(heater, LOW);
  return resistance;
}

#endif
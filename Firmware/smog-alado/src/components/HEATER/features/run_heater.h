#if !defined(RUN_HEATER)
#define RUN_HEATER

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"
// ADICIONAR AQUI OS IMPORTS DE LIBS NECESSÁRIOS.

void runHeater(int preset)
{
  power = 0;
  error = tempGoal - heaterTemperature;

  if (preset > 0)
  {
    if (heaterTemperature < tempMax)
    {
      if (error > 20)
        power = 100 * ANALOG_RANGE / 100;
      else
      {
        integral += (error * KI);
        if (integral > 40)
          integral = 40;
        if (integral < -40)
          integral = -40;
        proportional = error * KP;
        power = 0.4 * ANALOG_RANGE + proportional + integral;
        if (power > ANALOG_RANGE)
          power = ANALOG_RANGE;
        if (power < 0)
          power = 0;
      }
    }
  }
  powerPercent = 100 * power / ANALOG_RANGE;
  if (power > 0)
  {
    analogWrite(heater, power);
  }
  else
    digitalWrite(heater, LOW);
}

#endif // RUN_HEATER

#if !defined(RUN_HEATER)
#define RUN_HEATER

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"
// ADICIONAR AQUI OS IMPORTS DE LIBS NECESSÁRIOS.

void runHeater(int preset)
{
  power = 0;
  prevError = error;
  error = tempGoal - heaterTemperature;

  if (preset > 0)
  {
    if (heaterTemperature < tempMax)
    {
      if (error > 20)
        power = 100 * ANALOG_RANGE / 100;
      else
      {
        proportional = error * KP;
        integral += ((error + prevError) / 2.0) * KI;  // Trapezoidal rule for integration
        derivative = (error - prevError) * KD;
        if (integral > 600)
          integral = 600;
        if (integral < -600)
          integral = -600;
        if (derivative > 300)
          derivative = 300;
        if (derivative < -300)
          derivative = -300;
        power = (proportional + integral + derivative);
        if (power > 100)
          power = 100;
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

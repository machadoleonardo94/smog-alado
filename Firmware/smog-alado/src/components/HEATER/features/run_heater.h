#if !defined(RUN_HEATER)
#define RUN_HEATER

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"
// ADICIONAR AQUI OS IMPORTS DE LIBS NECESSÁRIOS.

void runHeater(int preset)
{
  powerPercent = 100 * power / ANALOG_RANGE;

  if (power > 0)
  {
    analogWrite(heater, power);
  }
  else
    digitalWrite(heater, LOW);
}

#endif // RUN_HEATER
#if !defined(RUN_HEATER)
#define RUN_HEATER

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"
// ADICIONAR AQUI OS IMPORTS DE LIBS NECESSÁRIOS.

void runHeater()
{
  if (heaterTemperature >= tempMax)
  {
    digitalWrite(heater, LOW);
    digitalWrite(ledPin, LOW);
    powerPercent = 0;
    heaterStatus = false;
  }
  else 
  {
    while (globalTimer - windowStartTime > WindowSize) 
    {
      windowStartTime += WindowSize;
    }
    if (power > globalTimer - windowStartTime) 
    {
      digitalWrite(heater, HIGH);
      digitalWrite(ledPin, HIGH);
      heaterStatus = true;
    }
    else 
    {
      digitalWrite(heater, LOW);
      digitalWrite(ledPin, LOW);
      heaterStatus = false;
    }
    powerPercent = (power * 100) / WindowSize;
  }
}

#endif // RUN_HEATER
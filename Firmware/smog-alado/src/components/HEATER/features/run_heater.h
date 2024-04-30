#if !defined(RUN_HEATER)
#define RUN_HEATER

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"
// ADICIONAR AQUI OS IMPORTS DE LIBS NECESSÁRIOS.

void runHeater()
{
  if (power < WindowPID) 
  {
    digitalWrite(heater, HIGH);
    digitalWrite(ledPin, HIGH);
    powerPercent = 100;
  }
  else 
  {
    digitalWrite(heater, LOW);
    digitalWrite(ledPin, LOW);
    powerPercent = 0;
  }
}

#endif // RUN_HEATER
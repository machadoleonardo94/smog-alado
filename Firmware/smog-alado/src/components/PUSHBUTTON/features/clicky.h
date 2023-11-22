#if !defined(RUN_PUSHBUTTON)
#define RUN_PUSHBUTTON

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"

int buttonPress(int button)
{
  int count = 0;
  while (!digitalRead(button))
  {
    count++;
    delay(1);
  }
  if (count > 1000)
    return 2;
  if (count > 20)
    return 1; 
  else
    return 0;
}

#endif // PUSHBUTTON

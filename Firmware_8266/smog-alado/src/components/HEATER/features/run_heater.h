#if !defined(RUN_HEATER)
#define RUN_HEATER

#include "shared/dependencies.h"
//* Adicione o arquivo setup.h caso a feature atual faça uso de outras features do mesmo componente.
// #include "components/0-TEMPLATE/setup.h"
// ADICIONAR AQUI OS IMPORTS DE LIBS NECESSÁRIOS.

void runHeater(int preset) {
  // Calculate dimming value based on PID output (power)
  dimming = map(power, 0, ANALOG_RANGE, 8333, 1000); // Adjust mapping as needed

  static unsigned long lastZeroCross = 0;
  unsigned long now = micros();

  if (zeroCrossingDetected) {
    lastZeroCross = now;
    zeroCrossingDetected = false;
  }

  if ((now - lastZeroCross) >= dimming) {
    digitalWrite(triacPin, HIGH); // Trigger triac
    delayMicroseconds(50);      // Short pulse to trigger
    digitalWrite(triacPin, LOW);
  }
}

void zeroCrossingISR() {
  zeroCrossingDetected = true;
}

#endif // RUN_HEATER
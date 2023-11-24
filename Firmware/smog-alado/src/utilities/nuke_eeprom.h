#if !defined(CLEAR_EEPROM)
#define CLEAR_EEPROM

#include "shared/dependencies.h"

void clear_eeprom() {
  EEPROM.begin(512);
  // write a 0 to all 512 bytes of the EEPROM
  for (int i = 0; i < 512; i++) { EEPROM.write(i, 0); }
  EEPROM.end();
}

#endif // CLEAR_EEPROM
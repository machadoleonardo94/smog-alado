#if !defined(PID)
#define PID

#include "shared/dependencies.h"

void savePIDParametersToEEPROM();
void readPIDParametersFromEEPROM();

void setupPID()
{
  readPIDParametersFromEEPROM();
  myPID.SetOutputLimits(0, ANALOG_RANGE);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(100);
  myPID.SetTunings(Kp, Ki, Kd);
}

// Read PID values stored on EEPROM
void readPIDParametersFromEEPROM()
{
  EEPROM.get(EEPROM_KP_ADDRESS, Kp);
  EEPROM.get(EEPROM_KI_ADDRESS, Ki);
  EEPROM.get(EEPROM_KD_ADDRESS, Kd);

  // Update PID controller with the read values
  myPID.SetTunings(Kp, Ki, Kd);
}

void savePIDParametersToEEPROM()
{
  // Store new values in EEPROM
  EEPROM.put(EEPROM_KP_ADDRESS, Kp);
  EEPROM.put(EEPROM_KI_ADDRESS, Ki);
  EEPROM.put(EEPROM_KD_ADDRESS, Kd);
  EEPROM.commit();
}

void changeAutoTune()
{
}

#endif // TUNE_PID
#if !defined(TUNE_PID)
#define TUNE_PID

#include "shared/dependencies.h"

boolean useSimulation = false;  // Moved from the provided code to the beginning of the file
byte ATuneModeRemember = 2;

double kpmodel = 1.5, taup = 100, theta[50];
double outputStart = 5;
double aTuneStep = (ANALOG_RANGE / 50), aTuneNoise = (0.25), aTuneStartValue = 250;
unsigned int aTuneLookBack = 30;

//boolean tuning = false;
unsigned long modelTime, serialTime;

void changeAutoTune();
void AutoTuneHelper(bool start);

void autoTunePID()
{
  if (useSimulation)
  {
    for (byte i = 0; i < 50; i++)
    {
      theta[i] = outputStart;
    }
    modelTime = 0;
  }

  // Setup the pid
  myPID.SetMode(AUTOMATIC);

  if (tuning)
  {
    tuning = false;
    changeAutoTune();
    tuning = true;
  }

  if (tuning)
  {
    byte val = aTune.Runtime();
    if (val != 0)
    {
      tuning = false;
    }
    if (!tuning)
    {
      // We're done, set the tuning parameters
      Kp = aTune.GetKp();
      Ki = aTune.GetKi();
      Kd = aTune.GetKd();
      myPID.SetTunings(Kp, Ki, Kd);
      AutoTuneHelper(false);
    }
  }
  else
  {
    myPID.Compute();
  }

  if (useSimulation)
  {
    theta[30] = power;
    unsigned long now = millis();
    if (now >= modelTime)
    {
      modelTime += 100;
      // Simulated model computation
      for (byte i = 0; i < 49; i++)
      {
        theta[i] = theta[i + 1];
      }
      heaterTemperature = (kpmodel / taup) * (theta[0] - outputStart) + heaterTemperature * (1 - 1 / taup) + ((float)random(-10, 10)) / 100;
    }
  }
  else
  {
    analogWrite(0, power);
  }
}

void changeAutoTune()
{
  if (!tuning)
  {
    // Set the output to the desired starting frequency.
    power = aTuneStartValue;
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec((int)aTuneLookBack);
    AutoTuneHelper(true);
    tuning = true;
  }
  else
  {
    // Cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void AutoTuneHelper(bool start)
{
  if (start)
    ATuneModeRemember = myPID.GetMode();
  else
    myPID.SetMode(ATuneModeRemember);
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

#endif // TUNE_PID
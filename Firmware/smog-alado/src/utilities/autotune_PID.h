#if !defined(TUNE_PID)
#define TUNE_PID

#include "shared/dependencies.h"

boolean useSimulation = false;  // Moved from the provided code to the beginning of the file
byte ATuneModeRemember = 2;

double kpmodel = 1.5, taup = 100, theta[50];
double outputStart = 5;
double aTuneStep = (ANALOG_RANGE / 50), aTuneNoise = (0.5), aTuneStartValue = 100;
unsigned int aTuneLookBack = 60;

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

  /*
  if (!useSimulation)
  {
    // Pull the input in from the real world
    heaterTemperature;
  }
  */

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
      TKp = aTune.GetKp();
      TKi = aTune.GetKi();
      TKd = aTune.GetKd();

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



/*
{
  // Set the parameters for auto-tuning
  //double input = heaterTemperature;
  //double output = power;
  //double setpoint = tempGoal;

  // Create an instance of the PID_AutoTune class
  //PID_ATune aTune(&input, &output);

  // Set the desired tuning parameters
  aTune.SetNoiseBand(0.2); // Set the noise band (adjust as needed)
  aTune.SetOutputStep(ANALOG_RANGE / 100); // Set the output step (adjust as needed)
  aTune.SetLookbackSec(60); // Set the lookback time in seconds (adjust as needed)

  // Run the auto-tuning algorithm
  bool tuning = aTune.Runtime();
  
  if (tuning) {
    // Auto-tuning is still in progress
    Serial.println("AutoTune: Tuning...");
    TelnetStream.println("AutoTune: Tuning...");
  } else {
    // Auto-tuning is complete
    Serial.println("AutoTune: Complete!");
    // Get the tuned parameters
    TKp = aTune.GetKp();
    TKi = aTune.GetKi();
    TKd = aTune.GetKd();

    Kp = aTune.GetKp();
    Ki = aTune.GetKi();
    Kd = aTune.GetKd();

    TelnetStream.println("Tuned PID Parameters:");
    TelnetStream.print("Kp: ");
    TelnetStream.println(Kp);
    TelnetStream.print("Ki: ");
    TelnetStream.println(Ki);
    TelnetStream.print("Kd: ");
    TelnetStream.println(Kd);

    // Apply the tuned parameters to the PID controller
    myPID.SetTunings(Kp, Ki, Kd);
  }
}
*/

  /*
  // Run the auto-tuning algorithm
  tuning = aTune.Runtime();  

  if(tuning)
  {
    byte autoTuneResult = (aTune.Runtime());
    if (autoTuneResult!=0)
    {
      tuning = false;
    }
    if(!tuning) //we're done, set the tuning parameters
    { 
      TKp = aTune.GetKp();
      TKi = aTune.GetKi();
      TKd = aTune.GetKd();

      Kp = TKp;
      Ki = TKi;
      Kd = TKd;

      myPID.SetTunings(Kp,Ki,Kd);

      // Print the tuned parameters to Telnet
      TelnetStream.println("Tuned PID Parameters:");
      TelnetStream.print("New Kp: ");
      TelnetStream.println(Kp);
      TelnetStream.print("New Ki: ");
      TelnetStream.println(Ki);
      TelnetStream.print("New Kd: ");
      TelnetStream.println(Kd);

      AutoTuneHelper(false);
    }
  }
  else myPID.Compute();
}

void changeAutoTune()
{
 if(!tuning)
  {
    // Set the desired tuning parameters
    aTune.SetNoiseBand(0.5); // Set the noise band (adjust as needed)
    if (error < 50)
    {
      aTune.SetOutputStep(ANALOG_RANGE / 100); // Set the output step (adjust as needed)
    }
    aTune.SetLookbackSec(30); // Set the lookback time in seconds (adjust as needed)
    AutoTuneHelper(true);
    tuning = true;
  }
  else  
  { //cancel autotune
    aTune.Cancel();
    tuning = false;
    AutoTuneHelper(false);
  }
}

void AutoTuneHelper(bool start)
{
  if(start)
    ATuneModeRemember = myPID.GetMode();
  else
    myPID.SetMode(ATuneModeRemember);
}
*/

#endif // TUNE_PID
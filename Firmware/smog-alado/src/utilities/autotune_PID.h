#if !defined(TUNE_PID)
#define TUNE_PID

#include "shared/dependencies.h"

void AutoTuneHelper(bool start);

void autoTunePID()
{
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
    aTune.SetNoiseBand(0.2); // Set the noise band (adjust as needed)
    if (error < 50)
    {
      aTune.SetOutputStep(ANALOG_RANGE / 100); // Set the output step (adjust as needed)
    }
    else
    {
      aTune.SetOutputStep(ANALOG_RANGE / 10);
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


#endif // TUNE_PID
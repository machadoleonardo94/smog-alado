#if !defined(PROJECT_GLOBAL_CONSTANTS)
#define PROJECT_GLOBAL_CONSTANTS

//* Multiplier to convert microseconds to seconds.
#define one_second_in_microseconds 1000000


//* Sampling timers
#define SAMPLING_TIMER 10                       //delay between counting increments
#define SAMPLES_TO_SEC 1000/SAMPLING_TIMER      //how many increments every 1s 

//* Sleep timer
#define TIME_TO_SLEEP 10 * 60 * SAMPLES_TO_SEC - 1 

//* PID constants for heating control
#define KP 12
#define KI 0.15
#define KD 150

//* Temperature limit to avoid burnout
#define tempMax 205

//* Pulldown resistor R10
#define PULLDOWN 4700

//* Higher resolution for PWM output (default 256)
#define ANALOG_RANGE 1024

//* EEPROM addresses for wifi
#define EEPROM_WIFI_SSID_START 0
#define EEPROM_WIFI_PASS_START 64

//* EEPROM addresses for PID
//#define EEPROM_KP_ADDRESS 128
//#define EEPROM_KI_ADDRESS 132
//#define EEPROM_KD_ADDRESS 136

//* Paramethers for OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C

#endif // PROJECT_GLOBAL_CONSTANTS

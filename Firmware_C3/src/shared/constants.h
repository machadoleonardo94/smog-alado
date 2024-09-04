#if !defined(PROJECT_GLOBAL_CONSTANTS)
#define PROJECT_GLOBAL_CONSTANTS

//* Multiplier to convert microseconds to seconds.
#define one_second_in_microseconds 1000000

//* Sampling timers
#define SAMPLING_TIMER 10                    // delay between counting increments
#define SAMPLES_TO_SEC 1000 / SAMPLING_TIMER // how many increments every 1s

//* Sleep timer
#define TIME_TO_SLEEP minutes * 60 * SAMPLES_TO_SEC - 1

//* Time zone for NTP time sync
#define TIME_ZONE TZ_America_Sao_Paulo

//* Temperature limit to avoid burnout
#define tempMax 205

//* Pulldown resistor R10
#define PULLDOWN_RES 4700

//* Higher resolution for PWM output (default 256)
#define ANALOG_RANGE 1024

//* EEPROM addresses for wifi
#define EEPROM_WIFI_SSID_START 128
#define EEPROM_WIFI_PASS_START 192

//* EEPROM addresses for PID
#define EEPROM_KP_ADDRESS 0
#define EEPROM_KI_ADDRESS 32
#define EEPROM_KD_ADDRESS 64

#endif // PROJECT_GLOBAL_CONSTANTS

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>


#define ledPin 2
#define SDA 4
#define SCL 5
#define buttonPin 12
#define heater 14

#define kp 6
#define ki 0.2
#define tempMax 260
#define ANALOG_RANGE 1024


// put function declarations here:
double resCalc ();
double steinhart (double termistor);
void runHeater (int preset);
int buttonPress (int button);

Adafruit_ADS1115 ads;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(heater, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(ledPin, LOW); //builtin LED set to ON on boot
  digitalWrite(heater, LOW);  //heater set to OFF on boot
  if (!(ads.begin())){
    Serial.println("Failed to initialize ADS.");
  }
  ads.setGain(GAIN_ONE);
  Serial.begin(115200);
  Serial.println("setup");
  WiFi.mode(WIFI_OFF);
  analogWriteRange(ANALOG_RANGE);
}

double thermistor = 500;
double heaterTemperature = 0;
double tempGoal = 235;
double error = 0;
double integral = 0;
double proportional = 0;
int power = 0;
int preset = 0;
bool debouncedButton = false;
bool state = false;
uint16_t adcRaw = 1000;
uint16_t adcFiltered = 1000;

double adcTimer = 0;
double heaterTimer = 0;
double loopTimer = 0;

void loop() {
  if ((millis()-adcTimer) > 200){
    adcTimer = millis();
    thermistor = resCalc();
    heaterTemperature = steinhart(thermistor);
    runHeater(preset);
  }

  if (!digitalRead(buttonPin)){
    debouncedButton = buttonPress(buttonPin);
    if (debouncedButton){
      preset++;
    }
    Serial.printf("Clict Clect \n");
    delay(100);
    if (preset >= 4)
      preset = 0;
  }

  if ((millis()-loopTimer) > 1000){
    loopTimer=millis();
    digitalWrite(ledPin, state);
    state = !(state);
    double powerPercent = 100*power/ANALOG_RANGE;
    Serial.print(">Thermistor resistence: ");
    Serial.println(thermistor);
    Serial.print(">Temperature reading: ");
    Serial.println(heaterTemperature);
    Serial.print(">Power output: ");
    Serial.println(powerPercent);
    Serial.print(">Filtered ADC: ");
    Serial.println(adcFiltered);    
  }
}

// put function definitions here:
double resCalc (){
  int pulldownResistor = 4700;
  double resistor = 0;
  adcRaw = ads.readADC_SingleEnded(0);
  adcFiltered = 0.9 * adcFiltered + 0.1 * adcRaw;
  double adcVoltage = ads.computeVolts(adcFiltered);
  resistor = (3.3 / (adcVoltage)) * pulldownResistor - pulldownResistor;
  if (resistor <200 )
    resistor = 200;
  if (resistor > 120000)
    resistor = 120000;
  return resistor;
}

double steinhart (double termistor){
  const static double  a = 0.0008002314855002526;
  const static double  b = 0.0001989545566222665;
  const static double  c = 1.7249962319615102e-7;

  // Utilizes the Steinhart-Hart Thermistor Equation:
  // Temperature in Kelvin = 1 / {A + B[ln(R)] + C[ln(R)]^3}
  double ln_r = log(termistor); // Saving the Log(resistance) so not to calculate it 4 times later.
  float temperature = (1 / (a + (b * ln_r) + (c * ln_r * ln_r * ln_r))) - 273.15; //Convert K to ºC
  return (temperature); 
}

void runHeater(int preset){
  power = 0;
  error = tempGoal - heaterTemperature;
  switch (preset){
    case 0:
      power = 0;
      break;
    case 1: //open loop preheating at 20% power
      if (heaterTemperature < 140)
        power = 20*ANALOG_RANGE/100;
      else
        power = 0;;
      break;
    case 2: //open loop preheating at 40% power
          if (heaterTemperature < 200)
        power = 40*ANALOG_RANGE/100;
      else
        power = 0;
      break;
    case 3: 
      if (heaterTemperature < tempMax){
        if (error > 10)
          power = 80*ANALOG_RANGE/100;
        else {
          integral += (error * ki);
          if (integral > 12) integral = 12;
          if (integral < -12) integral = -12;
          proportional = error * kp;
          power = 0.4*ANALOG_RANGE + proportional + integral;
          if (power>ANALOG_RANGE) power = ANALOG_RANGE;
        }
      } 
      break;
    default:
      Serial.printf("No valid power option \n");
  }
  if (power > 0)
    analogWrite (heater, power);
  else
    digitalWrite (heater, LOW);
  Serial.print(">Proportional part: ");
  Serial.println(proportional);
  Serial.print(">Integral part: ");
  Serial.println(integral);  
}

int buttonPress(int button) {
  int count = 0;
  while(!digitalRead(button)){
    count++;
    delay(10);
  if (count>10)
    return 1;
  }
  return 0; 
}
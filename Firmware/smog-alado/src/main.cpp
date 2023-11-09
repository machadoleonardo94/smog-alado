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

#define kp 1
#define ki 0.05
#define tempMax 235


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
  WiFi.mode(WIFI_OFF);
}

double heaterTemperature = 0;
double tempGoal = 220;
double error = 0;
double integral = 0;
int preset = 3;
bool debouncedButton = false;
bool state = false;

double adcTimer = 0;
double loopTimer = 0;

void loop() {
  if ((millis()-adcTimer) > 200){
    adcTimer = millis();
    heaterTemperature = steinhart(resCalc());
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
    Serial.printf("Thermistor resistence: %.1f \n", resCalc());
    Serial.printf("Temperature reading: %.1f \n", steinhart(resCalc()));
  }
}

// put function definitions here:
double resCalc (){
  int pulldownResistor = 4700;
  double resistor = 0;
  uint16_t adcRaw = 1000;
  adcRaw = ads.readADC_SingleEnded(0);
  resistor = (32768 / (adcRaw)) * pulldownResistor - pulldownResistor;
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
  int power = 0;
  float powerPercent = 0;
  error = tempGoal - heaterTemperature;
  switch (preset){
    case 0:
      power = 0;
      break;
    case 1: //open loop preheating at 20% power
      if (heaterTemperature < 140)
        power = 20*255/100;
      else
        power = 0;;
      break;
    case 2: //open loop preheating at 40% power
          if (heaterTemperature < 180)
        power = 40*255/100;
      else
        power = 0;
      break;
    case 3: 
      if (heaterTemperature < tempMax){
        if (error > 10)
          power = 200;
        else {
          integral += integral + (error * ki);
          if (integral > 20) integral = 20;
          if (integral < -20) integral = -20;
          power = 150 + error * kp + integral;
          if (power>255) power = 255;
        }
      } 
      break;
    default:
      Serial.printf("No valid power option \n");
  }
  powerPercent = 100 * power/255;
  Serial.printf ("PWM Heating %d \n", power);
  Serial.printf ("PWM Heating %.1f%% \n", powerPercent);
  if (power > 0)
    analogWrite (heater, power);
  else
    digitalWrite (heater, LOW);
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
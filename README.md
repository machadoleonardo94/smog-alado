# smog-alado
Desktop and portable heating element controller.

## Tested uses: 
* Precise temperature control for coffee machines
* SMD soldering hotbed
* Aromatherapy diffusers

## Current hardware versions: ESP12F and ESP32-C3
* ESP12F board noes not support wakeup from deep sleep, but accepts 12V input. Aimed at desktop devices running on external power sources. It also uses the integrated ADC that requires calibration.
* ESP32-C3 board includes deepsleep, 16bit 4channel ADC (two thermistors, input voltage and current on load), USB type-C connector (charging and programming) and a WS2812B LED for debug and fancy lights.
* The 12F hardware version is considered done and more accessible, while the C3 version is a work in progress. Current C3 PCB version has wiring mistakes and should be avoided while the C3V2 is being built.
* Both versions can be wired on perfboard using NodeMCU modules and an external MOSFET or SSR if the challanger is bold.

## Mileage may vary, use at your own risk.

Portable version with 1S2P 18650 battery and 510 connector:

<img src="https://github.com/user-attachments/assets/fa0723e2-6af2-440c-a0b0-192bf5949374" width="480">

Portable version with 2S1P 21700, homemade heating element:

<img src="https://github.com/user-attachments/assets/df4abeeb-7708-4ad2-8ddf-bf086642f4c5" width="480">

Current devkit:

<img src="https://github.com/user-attachments/assets/6e8d7228-225a-4b9b-a020-bce0da30d1f9" width="480">


## Main Features:
* PID heating to setpoint
* Single pushbutton control
* 0.96" OLED display
* OTA firmware upload
* Telnet debugging
* Auto power off

## Minimum required parts besides components BoM:
* 1x Power source
* 0.15mm NiCr wire
* Heat resistant cable  
* 1x RS232 USB to TTL module 
* 1x PCB
* 1x 100k NTC 3950 thermistor
* 1x 40N02 TO252 N-channel MOSFET or equivalent module
* 1x 12x12mm pushbutton (or whatever)
* 1x 0.96" OLED I2C display

## Recomended power sources (12F):
* 2S1P 21700 li-ion batteries with 2S BMS
* 2S lithium battery charger circuit
* 9V~12V 2A brick power supply

## Current issues (3C): 
* Missing GND connection on I2C connector;
* Button wrongly wired to 3V3. Cut the trace and connect directly to Vin;
* Gate driver does not hold MOSFET off, requires a bleeding resistor between gate and source MOSFET pins;
* 12 pin USB C connector is fucking terrible to solder correctly, so I've added an external header for serial programming and a backup 6 pin connector for charging;
* I had the dumb and forgot the antenna, so now I either solder an 1U footprint or deal with a lump on the 3D case.

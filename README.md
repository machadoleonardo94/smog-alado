# smog-alado
Desktop vaporizer project with 2S battery, homemade heating element and temperature control

![board](https://github.com/machadoleonardo94/smog-alado/assets/52208834/82a1beb1-0f0f-4a3b-9d36-1a72f8a2a4b8)

## Main Features:
* ESP-12F processor
* 100k NTC 3950 termistor
* 6ohm NiCr heating element
* 3D printed casing
* Customizable temperature target
* Tactile switch for inputs
* UART firmware upload
* Status LED

## Minimum required parts:
* 1x 8~12V 20W+ power source
* 1x 1m 0.15mm NiCr wire
* 1x RS232 USB to TTL module 
* 1x PCB
* 1x ESP-12F module
* 1x 100k NTC 3950 thermistor
* 2x 1x2 male header 1" spaced
* 1x AMS1117 3V3
* 1x 40N02 TO252 N-channel MOSFET
* 1x 2mm DC 2A+ panel power connector
* 1x 100nF 0805 ceramic capacitor
* 1x 22uF 1210 tantalum capacitor
* 2x 330 0805 resistor
* 2x 1k 0805 resistor
* 2x 2k2 0805 resistor
* 6x 10k 0805 resistor
* 2x 100k 0805 resistor
* 1x 220k 0805 resistor

## Recomended power sources:
* 2S1P 21700 li-ion batteries with 2S BMS
* 2S lithium battery charger circuit
* 9V~12V 2A brick power supply

## Suggested addons:
* GX16-4 panel connector (for heating element replacement)
* Lever or rotary switch (for hard turning off)
* Push button (for waking up and selecting presets)
* 1.25mm 4 pin JST SMD connector
* ADS1115 I2C 4 channel ADC
* 0.96" I2C LCD display
* 1x 2N7002 SOT23 N-channel mosfet (cannot be BJT, otherwise ESP won't turn on) 

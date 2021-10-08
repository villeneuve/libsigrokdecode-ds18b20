-------------------------------------------------------------------------------
Dallas DS18S20 1-Wire digital temperature sensor
-------------------------------------------------------------------------------

This is a capture example of the 1-Wire traffic from Maxim DS18S20 temperature sensor.

Details:
https://datasheets.maximintegrated.com/en/ds/DS18S20.pdf

Logic analyzer setup
--------------------

The logic analyzer used was a Saleae Logic 8MHz clone.

The capture was made directly from PulseView with these settings:  
- Channel 0, 1MHz, 1MS  
- trigger to falling edge  
- pre-trigger capture ratio = 1%  
And then saving the file: DS18S20_1u_Arduino_GetTemperature.sr  

Hardware setup:
--------------

Only one DS18S20 is connected: one 4k7 resistor between VCC and DQ  
VCC to Arduino Uno 3.3V  
GND to Arduino Uno GND  
DQ to Arduino Uno Pin 10  
GND to logic analyzer GND  
1k resistor between DQ and logic analyzer channel 0  

The Arduino sketch is almost an Arduino standard one.  
It's here:  
https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/dumps/ds18s20_GetTemperature/EssaiDS18B20_2.ino

The communication is as following:
 - Master sends a Reset (to trigger the record)
 - Master sends a Reset then a Search ROM command to enumerate all 1-Wire devices
 - Master-slaves communication ends with ROM found (hex) : 10 15 44 E6 01 08 00 20 (10 is DS18S20 family code)
 - Master sends a Match ROM command followed by this ROM 10 15 44 E6 01 08 00 20
 - Master sends a Convert command to request slave to start temperature conversion
 - Wait 750ms (time to perform temperature conversion)  
 - Master sends a Reset
 - Master sends a Match ROM command followed by this ROM 10 15 44 E6 01 08 00 20
 - Master sends a Read Scatchpad command
 - Slave 10 15 44 E6 01 08 00 20 answers with 9 bytes (T°=19.0000°C, TH, TL, Resolution= 9 bits )
 - Master sends a Reset

Here under an example of the output of the Arduino in a terminal:
-----------------------------------------------------------------
Search ROM: got one!.. ROM = 10 15 44 E6 1 8 0 20  
  Chip = DS18S20  
  Data = 1 26 0 4B 46 FF FF 10 10 8B  CRC=8B  
  Temperature = 18.75 Celsius, 65.75 Fahrenheit  
No more addresses.  
Added Guy delay 10s...  

Here under a screenshot of a portion of the capture:
----------------------------------------------------
with the 3 decoders stacked (1wire link layer, 1wire network layer, ds18b20):  

 
 <img src="https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/screenshots/Screenshot%202021-10-07%2017.15.42.png">

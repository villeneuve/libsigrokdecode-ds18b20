-------------------------------------------------------------------------------
Dallas DS18B20 1-Wire digital temperature sensor
-------------------------------------------------------------------------------

This is a capture example of the 1-Wire traffic from Maxim DS18B20 temperature sensor.

Details:
https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf

Logic analyzer setup
--------------------

The logic analyzer used was a Saleae Logic 8MHz clone.

The capture was made directly from PulseView with these settings:
- Channel 0, 1MHz, 2MS
- trigger to falling edge  
And then saving the file: DS18B20_2u_Arduino_1MHz_2MS_trigger.sr

Hardware setup:
--------------

Two DS18B20 are connected in // : GND to GND, DQ to DQ, VCC to VCC  
one 4k7 resistor between VCC and DQ  
VCC to Arduino Uno 3.3V  
GND to Arduino Uno GND  
DQ to Arduino Uno Pin 10  
GND to logic analyzer GND  
1k resistor between DQ and logic analyzer channel 0  

The Arduino sketch is almost an Arduino standard one.  
It's here:  
https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/dumps/GetTemperature/EssaiDS18B20_2.ino

The communication is as following:
 - Master sends a Reset (to trigger the record)
 - Master sends a Reset then a Search ROM command to enumerate all 1-Wire devices
 - Master-slaves communication ends with ROM found : 0x37041750386eff28 (28 is DS18B20 family code)
 - Master sends a Match ROM command followed by this ROM 0x37041750386eff28
 - Master sends a Convert command to request slave to start temperature conversion
 - Wait 750ms (time to perform temperature conversion @12 bits resolution as per datasheet)
 - Master sends a Reset
 - Master sends a Match ROM command followed by this ROM 0x37041750386eff28
 - Master sends a Read Scatchpad command
 - Slave 0x37041750386eff28 answers with 9 bytes (T°=19.4375°C)
 - Master sends 2 Resets then a Search ROM command to continue to enumerate all 1-Wire devices
 - Master-slaves communication ends with ROM found : 0x460217b07617ff28 (28 is DS18B20 family code)
 - Master sends a Match ROM command followed by this ROM 0x460217b07617ff28
 - Master sends a Convert command to request slave to start temperature conversion
 - Wait 750ms (time to perform temperature conversion @12 bits resolution as per datasheet)
 - Master sends a Reset
 - Master sends a Match ROM command followed by this ROM 0x460217b07617ff28
 - Master sends a Read Scatchpad command
 - Slave 0x460217b07617ff28 answers with 9 bytes (T°=19.625°C)
 - Master sends a Reset

Here under an example of the output of the Arduino in a terminal:
-----------------------------------------------------------------
Search ROM: got one!.. ROM = 28 FF 6E 38 50 17 4 37  
  Chip = DS18B20  
  Data = 1 3C 1 4B 46 7F FF C 10 36  CRC=36  
  Temperature = 19.75 Celsius, 67.55 Fahrenheit  
Search ROM: got one!.. ROM = 28 FF 17 76 B0 17 2 46  
  Chip = DS18B20  
  Data = 1 40 1 20 FF 1F FF 0 10 E6  CRC=E6  
  Temperature = 20.00 Celsius, 68.00 Fahrenheit  
No more addresses.  
Added Guy delay 10s...  

Here under a screenshot of a portion of the capture:
----------------------------------------------------
with the 3 decoders stacked (1wire link layer, 1wire network layer, ds18b20):  

 
 <img src="https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/screenshots/Screenshot 2021-10-02 11.40.04.png">

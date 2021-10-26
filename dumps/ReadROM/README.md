-----------------------------------------------------------
Dallas DS18B20 1-Wire digital temperature sensor
-------------------------------------------------------------------------------

This is a capture example of the 1-Wire traffic from Maxim DS18B20 temperature sensor.  
This example is the 'Read ROM' ROM Command (0x33)  
No more than 1 device must be on the bus!

Details:
https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf

Logic analyzer setup
--------------------

The logic analyzer used was a Saleae Logic 8MHz clone.

The capture was made directly from PulseView with these settings:
- Channel 0, 1MHz, 200kS
- trigger to falling edge  
- pre-trigger capture ratio = 1%  
And then saving the file: DS18B20_1u_Arduino_ReadROM.sr

Hardware setup:
--------------

Only one DS18B20 is connected:
one 4k7 resistor between VCC and DQ  
VCC to Arduino Uno 3.3V  
GND to Arduino Uno GND  
DQ to Arduino Uno Pin 10  
GND to logic analyzer GND  
1k resistor between DQ and logic analyzer channel 0  

The Arduino sketch is here:  
https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/dumps/ReadROM/TestDS18B20_ReadRom.ino  

The communication is as following:
 - Master sends a Reset (this falling edge triggers the PulseView record)
 - Master sends a Read ROM command
 - Slave answers with 8 bytes
 
Here under the output of the Arduino software in a terminal:
------------------------------------------------------------

Wait 10s before starting  
Go!  
ROM=28 FF 6E 38 50 17 4 37  CRC=37  
Done!  

Here under a screenshot of a portion of the capture:
----------------------------------------------------
with the 3 decoders stacked (1wire link layer, 1wire network layer, ds18b20):  

 
 <img src="https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/screenshots/Screenshot%202021-10-26%2015.56.22.png">

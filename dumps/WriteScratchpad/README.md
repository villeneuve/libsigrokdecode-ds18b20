-----------------------------------------------------------
Dallas DS18B20 1-Wire digital temperature sensor
-------------------------------------------------------------------------------

This is a capture example of the 1-Wire traffic from Maxim DS18B20 temperature sensor.
This example is about reading and writing the scratchpad memory

Details:
https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf

Logic analyzer setup
--------------------

The logic analyzer used was a Saleae Logic 8MHz clone.

The capture was made directly from PulseView with these settings:
- Channel 0, 1MHz, 500kS
- trigger to falling edge  
- pre-trigger capture ratio = 1%
And then saving the file: DS18B20_1u_Arduino_WriteScratchpad.sr

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
https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/dumps/ TODO!!!!!!!!!!!!!!!!!!!!

The communication is as following:
 - Master sends a Reset (this falling edge triggers the PulseView record)
 - Master sends a Skip ROM command
 - Master sends a Read Scatchpad function command
 - Slave answers with 9 bytes
 - Master sends a Reset
 - Master sends a Skip ROM command
 - Master sends a Write Scatchpad function command
 - Master sends 3 bytes to write to scratchpad (TH, TL, conf. register)
 - Wait 10us
 - Master sends a Reset
 - Master sends a Skip ROM command
 - Master sends a Read Scatchpad function command
 
 At the end we can confirm that we read the values we have written:
 1st read         : TH=74 TL=71 Config.=12bits
 read after write : TH=34 TL=-2 Config.=10bits
 This is confirmed with the PulseView capture and the here under terminal output

Here under the output of the Arduino software in a terminal:
------------------------------------------------------------

Wait 10s before starting  
Go!  
Data = 50 5 4A 47 7F FF 7F 10 5  CRC=5  
Data = 50 5 22 FE 3F FF 3F 10 A0  CRC=A0  

Here under a screenshot of a portion of the capture:
----------------------------------------------------
with the 3 decoders stacked (1wire link layer, 1wire network layer, ds18b20):  

 
 <img src="https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/screenshots/Screenshot%202021-10-04%2010.31.58.png">

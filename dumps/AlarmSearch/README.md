-----------------------------------------------------------
Dallas DS18B20 1-Wire digital temperature sensor
-------------------------------------------------------------------------------

This is a capture example of the 1-Wire traffic from Maxim DS18B20 temperature sensor.  
This example is about the Alarm search (0xEC) ROM COMMAND  

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

Two DS18B20 are connected in // : GND to GND, DQ to DQ, VCC to VCC  
one 4k7 resistor between VCC and DQ  
VCC to Arduino Uno 3.3V  
GND to Arduino Uno GND  
DQ to Arduino Uno Pin 10  
GND to logic analyzer GND  
1k resistor between DQ and logic analyzer channel 0  
 
The Arduino sketch is almost an Arduino standard one. The same as the GetTemperature example.  
The only change is this line:  
 if ( !ds.search(addr))  
 replaced by  
 if ( !ds.search(addr, 0))  // The 0 (False) will start a conditional search instead of normal search  
 The sketch is here: 
https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/dumps/ TODO!!!!!!!!!!!!!!!!!!!!  

The communication is as following:
 - Master sends a Reset (this falling edge triggers the PulseView record)
 - Master sends a Reset then an Alarm Search ROM command (only devices in alarm will answer)
 - Slave answers with 8 bytes.
 - Master-slaves communication ends with ROM found : 0x460217b07617ff28 (28 is DS18B20 family code)
 - Master sends a Match ROM command followed by this ROM 0x460217b07617ff28
 - Master sends a Convert command to request slave to start temperature conversion
 - Wait 750ms (time to perform temperature conversion @12 bits resolution as per datasheet)
 - Master sends a Reset
 - Master sends a Match ROM command followed by this ROM 0x460217b07617ff28
 - Master sends a Read Scatchpad command
 - Slave 0x460217b07617ff28 answers with 9 bytes (T°=20°C, TH=31, TL=27, Resolution=9bits)
 
 At the end we can confirm that:
 - Only 1 out 2 devices has reported an alarm state
 - This DS18B20 was actually in alarm because mesured temperature =20 is lower than TL=27

Here under the output of the Arduino software in a terminal:
------------------------------------------------------------

Search ROM: got one!.. ROM = 28 FF 17 76 B0 17 2 46  
  Chip = DS18B20  
  Data = 1 40 1 1F 1B 1F FF 1F 10 1E  CRC=1E  
  Temperature = 20.00 Celsius, 68.00 Fahrenheit  
No more addresses.  
Added Guy delay 10s...  

Here under a screenshot of a portion of the capture:
----------------------------------------------------
with the 3 decoders stacked (1wire link layer, 1wire network layer, ds18b20):  

 
 <img src="https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/screenshots/Screenshot 2021-10-02 11.40.04.png">

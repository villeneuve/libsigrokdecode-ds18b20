# libsigrokdecode-ds18b20
This is a decoder. A sigrok/PulseView onewire DS18B20 decoder  

It stacks on top of the 'onewire_network' PD and decodes the Maxim 1-Wire digital thermometers protocol.  
The decoders works the very popular DS18B20 1wire temperature sensor, but not only. 
It works for several devices: DS1822, DS1825, DS18S20, DS18B20, DS28EA00
This decoder is forked from DS28EA00 decoder made by Iztok Jeras  

It decodes data to give information such as temperature, high and low alarm thresholds, resolution. As shown on the below sceenshot:
 <img src="https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/screenshots/Screenshot%202021-10-01%2014.06.33.png">
 
This decoder gives more information, it decodes the 1wire protocol showing:
- commands
- 1wire ROM ID
- Measured temperature (after a CONVERT command has been issued)
- TH (high alarm threshold)
- TL (low alarm threshold)
- Resolution configuration (9-12bits)
- Read and write to the scratchpad and display the values
- Read and write to EEPROM and display the values
- Check power mode (parasite or powered)
- Check when temperature is ready after the convert command (when read slots are issued)
- Search alarm

It works with sigrok-cli as well.   
Example:  
$ sigrok-cli --driver fx2lafw --config samplerate=1000000 --channels D0 --samples 2000000 --wait-trigger --triggers D0=f -P onewire_link,onewire_network,ds18b20 | grep Temperature  
ds18b20-1: Temperature: 22.5000°C, TH: 32, TL: -1, Resolution: 9 bits  
ds18b20-1: Temperature: 22.0000°C, TH: 75, TL: 70, Resolution: 12 bits  

Dumps are provided in the dumps folder.  
The dumps are saved PulseView captures (*sr files) and can be open in PulseView (open file)  
The dumps are demonstrating 5 different one-wire commands:  
DS18B20: read scratchpad (and get temperature), read ROM, write scratchpad, search alarm  
DS18S20: read scratchpad (and get temperature)  
In each folder the README.md is explaining hardware, software and the result  

To use this decoder just copy the ds18b20 folder and its content in your /usr/share/libsigrokdecode/decoders/ folder (root owner and group)  
And restart PulseView  

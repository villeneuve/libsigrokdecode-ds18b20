# libsigrokdecode-ds18b20
This is a decoder. A sigrok/PulseView onewire DS18B20 decoder  

It stacks on top of the 'onewire_network' PD and decodes the Maxim 1-Wire digital thermometers protocol.  
The DS18B20 is a very popular 1wire temperature sensor.  
However this decoder works for several devices: DS1822, DS1825, DS18S20, DS18B20, DS28EA00
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

It works with sigrok-cli as well. Example:
$ sigrok-cli --driver fx2lafw --config samplerate=1000000 --channels D0 --samples 2000000 --wait-trigger --triggers D0=f -P onewire_link,onewire_network,ds18b20 | grep Temperature  
ds18b20-1: Temperature: 22.5000°C, TH: 32, TL: -1, Resolution: 9 bits  
ds18b20-1: Temperature: 22.0000°C, TH: 75, TL: 70, Resolution: 12 bits  


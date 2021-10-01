# libsigrokdecode-ds18b20
This is a decoder. A sigrok/PulseView onewire DS18B20 decoder  

It stacks on top of the 'onewire_network' PD and decodes the Maxim DS18B20 1-Wire digital thermometer protocol.  
The DS18B20 is a very popular 1wire temperature sensor.  
This DS18B20 decoder is forked from DS28EA00 decoder made by Iztok Jeras  

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

TODO:
- search alarm
- Make this decoder works for several 1wire temperature devices who share the same command and function protocol.

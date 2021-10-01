# libsigrokdecode-ds18b20
sigrok/PulseView onewire DS18B20 decoder that stacks on 1wire-network-layer decoder 

This decoder stacks on top of the 'onewire_network' PD and decodes the
Maxim DS18B20 1-Wire digital thermometer protocol.
This DS18B20 decoder is made from DS28EA00 decoder
Original DS28EA00 decoder made by Iztok Jeras
DS28EA00 and DS18B20 share many commands so this decoder should be usable with DS28EA00 as well.

https://github.com/villeneuve/libsigrokdecode-ds18b20/blob/main/screenshots/Screenshot%202021-10-01%2014.06.33.png

The DS18B20 is a very popular 1wire temperature sensor
This decoder decodes the 1wire protocol showing:
- commands
- 1wire ROM ID
- Temperature
- TH (high alarm threshold)
- TL (low alarm threshold)

TODO:
- Resolution configuration (9-12bits)
- More commands
- search alarm
- etc..

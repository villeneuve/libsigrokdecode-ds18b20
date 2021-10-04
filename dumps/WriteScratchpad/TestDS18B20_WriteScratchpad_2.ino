#include <OneWire.h>

// Test: read scratchpad, then write and read it again to check

OneWire  ds(10);  // on pin 10 (a 4.7K resistor is necessary)

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  byte i;
  byte data[12];
  byte addr[8];

  Serial.println("Wait 10s before starting");
  delay(10000);
  Serial.println("Go!");

  ds.reset();
  ds.write(0xCC);  // Skip ROM command we speak to all roms on the bus
  // Now we read. To do read after a skip rom no more than one device must be on the bus
  ds.write(0xBE);  // Read Scratchpad
  Serial.print("Data = ");
  for ( i = 0; i < 9; i++) {           // we read 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();

  ds.reset();
  ds.write(0xCC);  // Skip ROM
  ds.write(0x4E);  // Write scratchpad command
  ds.write(0x22);  // TH=34
  ds.write(0xFE);  // TL=-2 
  ds.write(0x3F);  // configuration register set resolution to 10 bits
  delay(10);       // let's wait a bit before reset
   
  // Now we read again to check what we have written
  ds.reset();
  ds.write(0xCC);  // Skip ROM command we speak to all roms on the bus
  // Now we read. To do read after a skip rom no more than one device must be on the bus
  ds.write(0xBE);  // Read Scratchpad
  Serial.print("Data = ");
  for ( i = 0; i < 9; i++) {           // we read 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print(OneWire::crc8(data, 8), HEX);
  Serial.println();
}

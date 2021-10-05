#include <OneWire.h>

// Test: read rom command. Only 1 device MUST be on the bus. No more!

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
  ds.write(0x33);  // Read ROM command 
  
  Serial.print("ROM=");
  for ( i = 0; i < 8; i++) {           // we need 9 bytes
    data[i] = ds.read();
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" CRC=");
  Serial.print( OneWire::crc8( data, 7), HEX);
  Serial.println();

  delay(1000);
  Serial.println("Done!");

}

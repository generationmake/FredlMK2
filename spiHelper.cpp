#include "spiHelper.h"

void setupSpiForTMC()
{
  SPI.begin();      // begin needs to be at the beginning
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.setDataMode(SPI_MODE3);

//  Serial.begin(9600); // should be configured in main programm
}

void sendSpiDataToTMC(unsigned long address, unsigned long datagram, int csPin, bool sendSerial)
{
  delay(100);
  uint8_t stat;
  unsigned long data;

  SPI.beginTransaction (SPISettings (100000, MSBFIRST, SPI_MODE3));

  digitalWrite(csPin,LOW);
  delayMicroseconds(10);

  stat = SPI.transfer(address);

  data |= SPI.transfer((datagram >> 24) & 0xff);
  data <<= 8;
  data |= SPI.transfer((datagram >> 16) & 0xff);
  data <<= 8;
  data |= SPI.transfer((datagram >> 8) & 0xff);
  data <<= 8;
  data |= SPI.transfer((datagram) & 0xff);
  digitalWrite(csPin,HIGH);
  SPI.endTransaction ();         // transaction over

  if(sendSerial)
  {
     Serial.print("Received: ");
     char tmp[16];
     uint16_t LSB = data & 0xffff;
     uint16_t MSB = data >> 16;
     sprintf(tmp, "0x%.2X%.4X%.4X", stat, MSB, LSB);
     Serial.print(tmp);
     Serial.print(" from register: ");
     Serial.println(address,HEX);
  }
}

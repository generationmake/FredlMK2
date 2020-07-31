#ifndef SPIHELPER_H
#define SPIHELPER_H

#include <Arduino.h>
#include <SPI.h>

void setupSpiForTMC();

void sendSpiDataToTMC(unsigned long address, unsigned long datagram, int csPin, bool sendSerial);
#endif

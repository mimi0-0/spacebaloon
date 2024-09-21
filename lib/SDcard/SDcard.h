#ifndef SDcard_h
#define SDcard_h
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>


void SD_Init();
void SD_Write(uint32_t data);


#endif
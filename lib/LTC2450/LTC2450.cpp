#include "LTC2450.h"
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#define LTC_CS_PIN   22

uint32_t readLTC2450() {
  uint32_t result = 0;
  
  // CSをLOWにして通信開始
  digitalWrite(LTC_CS_PIN, LOW);

  // 3バイトのデータを受信
  result |= SPI.transfer(0x00);  // 最初のバイト（MSB）
  result <<= 8;
  result |= SPI.transfer(0x00);  // 2番目のバイト
  result <<= 8;
  result |= SPI.transfer(0x00);  // 3番目のバイト（LSB）

  // CSをHIGHに戻して通信終了
  digitalWrite(LTC_CS_PIN, HIGH);

  return result;
}


#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Libtest.h>

Libtest tlib1;

void setup() {

  Serial.begin(9600);

}

void loop() {

  int value = tlib1.testMethod1();
  Serial.println(value);

  delay(1000);

}
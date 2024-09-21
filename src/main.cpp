#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Libtest.h>
#include <SDcard.h>
#include <LTC2450.h>
#include <Bluetooth.h>

unsigned long start_time = 0;
unsigned long keep_time = 0;

//時間後程調整
#define TIME 5400000

//チューブポンプ関連
#define IN1_PIN 14
#define IN2_PIN 12
#define PWM_PIN 13

#define HEATER_PIN 33
#define PELTIER_PIN 25
#define PUMP_LED_PIN 26
#define DETECTOR_PIN 27

#define SD_CS_PIN    5
#define LTC_CS_PIN   22

void setup() {
  
  Serial.begin(115200);
  pinMode(HEATER_PIN,OUTPUT);
  pinMode(PELTIER_PIN,OUTPUT);
  pinMode(PUMP_LED_PIN,OUTPUT);
  pinMode(DETECTOR_PIN,OUTPUT);

  pinMode(IN1_PIN,OUTPUT);
  pinMode(IN2_PIN,OUTPUT);

  ledcSetup(0, 12800, 8);
  ledcAttachPin(PWM_PIN, 0);

//highにすると停止
  digitalWrite(SD_CS_PIN, HIGH); 
  digitalWrite(LTC_CS_PIN, HIGH);

  SD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("start");
  if(millis() - start_time > TIME){
    digitalWrite(HEATER_PIN,HIGH);
    //いらないかも
    digitalWrite(PELTIER_PIN,HIGH);
    digitalWrite(PUMP_LED_PIN,HIGH);
    digitalWrite(DETECTOR_PIN,HIGH);

    digitalWrite(IN1_PIN,HIGH);
    digitalWrite(IN2_PIN,LOW);
    ledcWrite(0,250);
    keep_time = millis();
    Serial.println("start");
    while(millis() - keep_time < 100){
      uint32_t adcValue = readLTC2450();  // ADCからのデータを取得
      Serial.print("ADC Value: ");
      Serial.println(adcValue);  // 取得した値をシリアルモニターに表示 
    }
    digitalWrite(IN1_PIN,HIGH);
    digitalWrite(IN2_PIN,LOW);
    ledcWrite(0,170);
    while(millis() - keep_time < 300){
      uint32_t adcValue = readLTC2450();  // ADCからのデータを取得
      Serial.print("ADC Value: ");
      Serial.println(adcValue);  // 取得した値をシリアルモニターに表示 
    }
    digitalWrite(IN1_PIN,LOW);
    digitalWrite(IN2_PIN,LOW);
    ledcWrite(0,0);
    while(millis() - keep_time < 5000){
      uint32_t adcValue = readLTC2450();  // ADCからのデータを取得
      Serial.print("ADC Value: ");
      Serial.println(adcValue);  // 取得した値をシリアルモニターに表示 
    }
  }else{
    digitalWrite(HEATER_PIN,LOW);
    digitalWrite(PELTIER_PIN,LOW);
    digitalWrite(PUMP_LED_PIN,LOW);
    digitalWrite(DETECTOR_PIN,LOW);

    digitalWrite(IN1_PIN,LOW);
    digitalWrite(IN2_PIN,LOW);
    ledcWrite(0,0);
    delay(5000);
  }
}
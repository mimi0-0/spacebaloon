#include "SDcard.h"
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "SD.h"
//SPI V
#define SD_CS_PIN    4
#define SD_MOSI      23
#define SD_MISO      19
#define SD_SCK       18

/*//SPI H

#define SD_MOSI      27
#define SD_MISO      25
#define SD_SCK       26

#define SD_CS_PIN 14

*/

File myFile;
File iniFile
int fileNum;
char myName[16];
SPIClass SPISD(VSPI);

void SD_Init(){
  //  SPIClass SPI2(HSPI);

    SPISD.begin(SD_SCK, SD_MISO, SD_MOSI);
    if (!SD.begin(SD_CS_PIN,SPISD)) {  //SD_CS_PIN this pin is just the dummy pin since the SD need the input 
      Serial.println(F("failed!"));
      return;
    }
    else Serial.println(F("SD read!"));

    //ファイル番号設定
    String s1;
    String pres1;

    while(1){
        s1 = "/LOGFILE";
        if (fileNum < 10) {
            s1 += "00";
            s2 += "00";
        }else if(fileNum < 100) {
            s1 += "0";
            s2 += "0";
        }
        s1 += fileNum;
        s1 += ".csv";
        s1.toCharArray(myName, 16);
        if (!SD.exists(myName)) {
          myFile = SD.open(myName, FILE_WRITE);
          if (mainFile){
            Serial.print("Writing to test.txt...");
            mainFile.print("time,temperature,humidity,pressure,altitude\n");
            Serial.println("done.");
          }else{
              Serial.println("error opening test.txt to write");
          }
          break;
        }else{
          fileNum++;
        }
    }
}

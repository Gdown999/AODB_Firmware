#include <Arduino.h>
#include <Wire.h>
#include "I2CEEPROM.h"

// コンストラクタ
I2CEEPROM::I2CEEPROM(byte eepAdrTmp){
  eepromAdress = eepAdrTmp;
  Wire.begin();
}

byte I2CEEPROM::read(unsigned int dataAdress){
  byte data;
  Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
  Wire.write((int)(dataAdress >> 8));                // EEPROM内アドレス指定 MSB
  Wire.write((int)(dataAdress & 0xFF));              // LSB
  Wire.endTransmission();
  Wire.requestFrom(eepromAdress, 1);                  // 1バイトデータリクエスト
  while (Wire.available()) {                    //
    data = Wire.read();                         // データ受信
  }
  return data;
}

bool I2CEEPROM::write(unsigned int dataAdress, byte dataWrite){
  byte dataRead;
  Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
  Wire.write((int)(dataAdress >> 8));                // EEPROM内アドレス指定 MSB
  Wire.write((int)(dataAdress & 0xFF));              // LSB
  Wire.endTransmission();
  Wire.requestFrom(eepromAdress, 1);                  // 1バイトデータリクエスト
  while (Wire.available()) {                    //
    dataRead = Wire.read();                         // データ受信
  }

  if(dataWrite != dataRead){
    Wire.beginTransmission(eepromAdress);               // i2cアドレス指定
    Wire.write((int)(dataAdress >> 8));                // EEPROM内アドレス指定 MSB
    Wire.write((int)(dataAdress & 0xFF));              // LSB
    Wire.write(dataWrite);
    Wire.endTransmission();
    delay(5);
    return 1;
  }else{
    return 0;
  }
}

#include <Arduino.h>
#include "loopTime.h"

//コンストラクタ
loopTime::loopTime(void){
  unsigned long time = 0;
  unsigned long loopTime = 0;
  unsigned int hz = 0;
  int count = 0;
  bool boolSerialOut = 0;
}

//シリアル出力回数設定
void loopTime::setCount(int countTemp){
  count = countTemp;
}

//1周のタイムを出力
unsigned long loopTime::getTime(void){
  return loopTime;
}

//hzを出力
unsigned int loopTime::getHz(void){
  return hz;
}

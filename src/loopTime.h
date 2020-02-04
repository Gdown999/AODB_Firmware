#ifndef INCLUDED_LOOPTIME_h_
#define INCLUDED_LOOPTIME_h_

class loopTime{
public:
  //コンストラクタ
  loopTime();
  //チェックポイント
  void loopTimeCheck(void);
  //シリアル出力回数設定
  void setCount(int countTemp);
  //1周のタイムを出力
  unsigned long getTime(void);
  //hzを出力
  unsigned int getHz(void);
private:
  unsigned long time;
  unsigned long loopTime;
  unsigned int hz;
  int count;
  bool boolSerialOut;
};
//チェックポイント
inline void loopTime::loopTimeCheck(void){

  if (boolSerialOut) {
    if (count > 0 || count == -1) {
      Serial.print(hz); Serial.print("Hz--"); Serial.print(loopTime); Serial.println(F("ns"));
      if(count != -1)count -= 1;
    }
    boolSerialOut = 0;
    time = micros();

  }else{
    loopTime = micros() - time;
    hz = abs(1000000/loopTime);
    boolSerialOut = 1;
  }


}
#endif

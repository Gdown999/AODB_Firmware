#include <Keyboard.h>
#include <Mouse.h>
#include "U8glib.h"
#include "Keydefine.h"
#include <Wire.h>
/*#include <frequencyToNote.h>
#include <MIDIUSB.h>
#include <MIDIUSB_Defs.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>*/
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);
//ダイオードは縦配線から横配線へ流れるようにつなぐ
////////////////////////////////////////////////////////////
//timer
unsigned long arduino_time;
int ArTiHz;
long loading = 0;
int timeCount;
const byte register_num[2][22] = {//１段目はポート番号(Aが最初、1から始まる)(0は無効)、２段目はビット番号
///0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21
  {4, 4, 4, 4, 4, 3, 4, 5, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 6, 6, 6, 6,},
  {2, 3, 1, 0, 4, 6, 7, 6, 4, 5, 6, 0, 0, 0, 3, 1, 2, 0, 7, 6, 5, 4,},
};
///////////////////////////////////////////////////////////
//RW
bool Loop = true;
const char keyCode[219][5] PROGMEM = {//KC
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "NUL" ,"SOH" ,"STX" ,"ETX" ,"EOT" ,"ENQ" ,"ACK" ,"BEL" ,"BS"  ,"TAB" ,"LF"  ,"VT"  ,"FF"  ,"CR"  ,"SO"  ,"SI"  ,//0
  "DLE" ,"DC1" ,"DC2" ,"DC3" ,"DC4" ,"NAK" ,"SYN" ,"ETB" ,"CAN" ,"EM"  ,"SUB" ,""    ,"FS"  ,"GS"  ,"RS"  ,"US"  ,//1
  "SPC" ,"EXLM","DQUO","HASH","DLR" ,"PERC","AMPR","QUOT","LPRN","RPRN","ASTR","PLUS","COMM","MINS","DOT" ,"SLSH",//2
  "0"   ,"1"   ,"2"   ,"3"   ,"4"   ,"5"   ,"6"   ,"7"   ,"8"   ,"9"   ,"COLN","SCLN","LABK","EQL" ,"RABK","QUES",//3
  "AT"  ,"SFTA","SFTB","SFTC","SFTD","SFTE","SFTF","SFTG","SFTH","SFTI","SFTJ","SFTK","SFTL","SFTM","SFTN","SFTO",//4
  "SFTP","SFTQ","SFTR","SFTS","SFTT","SFTU","SFTV","SFTW","SFTX","SFTY","SFTZ","LBRC","BSLS","RBRC","CIRC","ANBR",//5
  "GRV" ,"A"   ,"B"   ,"C"   ,"D"   ,"E"   ,"F"   ,"G"   ,"H"   ,"I"   ,"J"   ,"K"   ,"L"   ,"M"   ,"N"   ,"O"   ,//6
  "P"   ,"Q"   ,"R"   ,"S"   ,"T"   ,"U"   ,"V"   ,"W"   ,"X"   ,"Y"   ,"Z"   ,"LCBR","PIPE","RCBR",""    ,"DEL" ,//7
  "LCTL","LSFT","LALT","LGUI","RCTL","RSFT","RALT","RGUI",""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,//8
  ""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,//9
  ""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,//A
  "ENT" ,"ESC" ,"BSPC","TAB" ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,//B
  ""    ,"CAPS","F1"  ,"F2"  ,"F3"  ,"F4"  ,"F5"  ,"F6"  ,"F7"  ,"F8"  ,"F9"  ,"F10" ,"F11" ,"F12" ,""    ,""    ,//C
  ""    ,"INS" ,"HOME","PGUP","DEL" ,"END" ,"PGDN","RGHT","LEFT","DOWN","UP"  ,                                   //D
};
const char mouseCode[6][5] PROGMEM = {//MC
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "LC"  ,"RC"  ,"MC"  ,"HU"  ,"HD"  ,"P"//0
};
const char layerCode[4][5] PROGMEM = {//LAY
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "00"  ,"01"  ,"02"  ,"03"//0
};
const char customCode[16][5] PROGMEM = {//CC
  //0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
  "OSU" ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,""    ,//0
};
////////////////////////////////////////////////////////////
//EEPROM
#define EEPROM_ADDRESS 0x50
////////////////////////////////////////////////////////////
//oled
unsigned long oledSleep_time;
bool oledState = 0;//oledが光っているなら真、消えているなら偽
byte oled_X;
byte oled_Y;
byte key_BoxX;
byte key_BoxY;
/////////////////////////////////////////////////////////////////
//serial1設定
byte ser1_recv;
byte ser1_send_key;
byte ser1_send_joy;

bool ser1_keyState;
byte ser1_row;
byte ser1_col;

byte ser1_mode;

bool ser1_joyState;
byte ser1_joynum;
/////////////////////////////////////////////////////////////////
//↓キーボード設定
#define division_num 2 //キーボードの分割数
#define layerNum 3 //レイヤーの数
const byte direction[division_num] = {0,1}; //01:Left, 10:Right
const byte rowNum = 4; //縦に並んでいるピン数
const byte colNum = 7; //横に並んでいるピン数
const byte rowPin[rowNum] = {4, 5, 6, 7}; //横列のピン番号
const byte colPin[colNum] = {21, 20, 19, 18, 15, 14, 16 }; //縦列のピン番号
word keyMap[division_num][rowNum][colNum];
word keyMap_temp[division_num][rowNum][colNum];
/*word keyMap_QWERTY[division_num][rowNum][colNum] =
{{
  {KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_____ },
  {KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_CAPS },
  {KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_EQL  },
  {KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_SPC  },
},{
  {KC_BSLS, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC },
  {KC_RBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MINS },
  {KC_LBRC, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT  },
  {KC_LSFT, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_QUOT },
}};*/
//char* keyMap_OLED[] = {"QWERTY","R6S","OSU!","Fortnite","ApexLegends","AviUtl","Division2",};//キーマップのOLEDの各文字列

bool currentState[rowNum][colNum]; //現在のキーの状態を保持する変数
bool beforeState[rowNum][colNum]; //前回のキーの状態を保持する変数
bool changeState[rowNum][colNum];//「i」は列の変数、「j」は行の変数
byte Switch_key[3][2] = {//切り替えモードに移行するためのスイッチの座標(Y座標、X座標)
  {1, 4},
  {2, 4},
  {3, 4}
};
byte Switch_KMode = 1;
byte Key_OSUindex_in = 0;
byte Key_OSUindex_out = 0;
/////////////////////////////////////////////////////////////////
//↓ジョイスティック設定
#define STX A9 //「STX」を「A1」に変換（ジョイスティックピン）
#define STY A8 //「STY」を「A0」に変換（ジョイスティックピン）
#define VR_IDLE 80 //ジョイスティックの補正範囲（０からの値）
int PDz = 420;//マウスの減速範囲
#define VRNG (500 - VR_IDLE)//分解能
static short vr[2]; //ジョイスティックの生の値
float pos[2];  //ジョイスティックの補正値
const byte stk_pins [2] = {STX, STY}; //ピンを変数配列に格納
const int JS_Dead_zone = 100; //ジョイスティックのデッドゾーン
int JS_Diagonal_Dead_zone = 190; //有効幅
word JSkeyMap[2][4];
word JSkeyMap_temp[2][4];
/*const word JSkeyMap_WASD[2][4] = {
  {KC_S   , KC_A   , KC_W   , KC_D   },
  {KC_DOWN, KC_LEFT, KC_UP  , KC_RGHT}};
const word JSkeyMap_MOUSE[2][4] = {
  {KC_DOWN, KC_LEFT, KC_UP  , KC_RGHT},
  {KC_DOWN, KC_LEFT, KC_UP  , KC_RGHT}};*/
bool currentJS[4] = {0, 0, 0, 0}; //ジョイスティックの現在の状態を記録（並びはキーコードと一緒）
bool beforeJS[4] = {0, 0, 0, 0}; //ジョイスティックの前回の状態を記録（並びはキーコードと一緒）
unsigned long MTime[2];
float M_point[2];
int M_PP[2];
/////////////////////////////////////////////////////////////////
//シリアル設定
byte trimStr_serial_count;//下記の符号の種類の数。
char* trimStr_serial[] =//どういう情報が送られてきたか判断するための符号。
//         0        1       2       3       4      5       6     7         8        9
  {"maplist","serial", "oled", "OLED","OLMAX","time","ASCII","BIN","keycode","RW",};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//経過時間関数
void loopTime(void){
  arduino_time = micros() - arduino_time;
  if (timeCount > 0 || timeCount == -1) {
    ArTiHz = abs(1000000/arduino_time);
    Serial.print(ArTiHz); Serial.print("Hz--"); Serial.print(arduino_time); Serial.println(F("ns"));
    if(timeCount != -1)timeCount -= 1;
  }
  arduino_time = micros();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//OLED表示メゾット（X座標、Y座標、”表示文字列”、二倍拡大有無）
void OLED_drawStr(byte X, byte Y, char* str, bool Twice) {
  u8g.firstPage();
  do {
    if (Twice == 1)u8g.setScale2x2();
    u8g.setFont(u8g_font_profont15r);
    u8g.drawStr( X, Y, str);
    if (Twice == 1)u8g.undoScale();
  } while ( u8g.nextPage() );
}
/////////////////////////////////////////////////////////////////
//切り替えアニメーション関数
void switchAnimation(void){
  bool Loop = true;
  bool loading_Return = true;
  unsigned long loading_interval = 0;
  do {
    if((loading_interval +500) < micros()){
      if (loading_Return == false) {
        if (loading >= 104) {
          loading_Return = true;
        } else loading += 16;
      } else if (loading_Return == true) {
        if (loading <= 0) {
          loading_Return = false;
        } else loading -= 4;
      }
      loading_interval = micros();
    u8g.firstPage();
    do {
      u8g.drawFrame(0,1,128,7);
      u8g.drawBox((loading), 2, 24, 5);
      u8g.setFont(u8g_font_profont15r);
      u8g.drawStr( 5, 20, F("loading..."));
    } while ( u8g.nextPage() );
    //Serial.println(loading);
  }
    for (byte z = 0; z < rowNum; z++) {//各スイッチの押されているか離されているかを一時保存する
      digitalWrite( rowPin[z], LOW );
      for (byte x = 0; x < colNum; x++) {
        //changeState[z][x] = digitalRead(colPin[x]);
        if(digitalRead(colPin[x]) == LOW){
          bool keyblock = LOW;
          keyMap_switch(z*colNum+x);
          do {
            keyblock = digitalRead(colPin[x]);
          }while (keyblock == LOW);
          Loop = false;
        }
      }
      digitalWrite( rowPin[z], HIGH );
    }
  } while (Loop);
  u8g.firstPage();
  do {
  } while ( u8g.nextPage() );
}
/////////////////////////////////////////////////////////////////
//キーマップ書き換えメゾット(キーマップ変数、ジョイススティックキーマップ変数、決定ボタン座標Y、決定ボタン座標X、OLED表示名)
/*void keyMap_Rewrite(word tmp_ary[division_num][rowNum][colNum], word tmp_JS[2][4], char* OLED_str) {
  for (byte l = 0; l < division_num; l++) {
    for (byte i = 0; i < rowNum; i++) {
      for (byte j = 0; j < colNum; j++) {
        if (l) {
          keyMap[l][i][colNum-1-j] = tmp_ary[l][i][j];//物理的な反転を書き込み時に修正する
        }else{
          keyMap[l][i][j] = tmp_ary[l][i][j];
        }
      }
    }
  }
  for(byte i = 0; i < 2; i++) {
    for (byte j = 0; j < 4; j++) {
      JSkeyMap[i][j] = tmp_JS[i][j];
    }
  }
  OLED_drawStr(0, 12, OLED_str, 0);
  Serial.print(F("KeyMap:"));
  Serial.println(OLED_str);
}*/
/////////////////////////////////////////////////////////////////
//キーマップ切り替えメゾット
void keyMap_switch(word c){
  switch (c) {
    //case 0:keyMap_Rewrite(keyMap_QWERTY, JSkeyMap_MOUSE, keyMap_OLED[c]);break;
    default:KMeepromRead(c);
  }
}
/////////////////////////////////////////////////////////////////
//http://radiopench.blog96.fc2.com/blog-entry-576.html
void i2cEEPROM_write(unsigned int eeADR, byte data ) {
  Wire.beginTransmission(EEPROM_ADDRESS);               // i2cアドレス指定
  Wire.write((int)(eeADR >> 8));                // EEPROM内アドレス指定 MSB
  Wire.write((int)(eeADR & 0xFF));              // LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5);                                     // 書き込み完了待ち
}
/////////////////////////////////////////////////////////////////
byte i2cEEPROM_read(unsigned int eeADR) {
  byte data;
  Wire.beginTransmission(EEPROM_ADDRESS);               // i2cアドレス指定
  Wire.write((int)(eeADR >> 8));                // EEPROM内アドレス指定 MSB
  Wire.write((int)(eeADR & 0xFF));              // LSB
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_ADDRESS, 1);                  // 1バイトデータリクエスト
  while (Wire.available()) {                    //
    data = Wire.read();                         // データ受信
  }
  return data;
}
/////////////////////////////////////////////////////////////////
//キーマップeeprom書き込み関数
void KMeepromWrite(unsigned int address){
  byte highByte = 0;
  byte lowByte = 0;
  address = address * 400;
  for (byte l = 0; l < division_num; l++) {
    for (byte i = 0; i < rowNum; i++) {
      for (byte j = 0; j < colNum; j++) {
        highByte = keyMap_temp[l][i][j] >> 8;
        lowByte = keyMap_temp[l][i][j] & 0xFF;
        i2cEEPROM_write(address,highByte);
        address++;
        i2cEEPROM_write(address,lowByte);
        address++;
      }
    }
  }
  for(byte i = 0; i < 2; i++) {
    for (byte j = 0; j < 4; j++) {
      highByte = JSkeyMap_temp[i][j] >> 8;
      lowByte = JSkeyMap_temp[i][j] & 0xFF;
      i2cEEPROM_write(address,highByte);
      address++;
      i2cEEPROM_write(address,lowByte);
      address++;
    }
  }
}
/////////////////////////////////////////////////////////////////
//キーマップeeprom読み取り関数
void KMeepromRead(word address){
  byte highByte = 0;
  byte lowByte = 0;
  address = address * 400;//マップブロック番号をアドレスに変換
  for (byte l = 0; l < division_num; l++) {
    for (byte i = 0; i < rowNum; i++) {
      for (byte j = 0; j < colNum; j++) {
        highByte = i2cEEPROM_read(address);
        address++;
        lowByte = i2cEEPROM_read(address);
        address++;
        if (l) {
          keyMap[l][i][colNum-1-j] = highByte << 8 | lowByte;
        }else{
          keyMap[l][i][j] = highByte << 8 | lowByte;
        }
      }
    }
  }
  for(byte i = 0; i < 2; i++) {
    for (byte j = 0; j < 4; j++) {
      highByte = i2cEEPROM_read(address);
      address++;
      lowByte = i2cEEPROM_read(address);
      address++;
      JSkeyMap[i][j] = highByte << 8 | lowByte;
    }
  }
}
/////////////////////////////////////////////////////////////////
//キー検出ループ
byte llkeylloop(void){
  byte llkeylloop_tmp = 0;
  for (byte i = 0; i < rowNum; i++) {
    fast_digitalWrite_LOW(rowPin[i]);
    for (byte j = 0; j < colNum; j++) {
      if(!fast_digitalRead(colPin[j])){
        llkeylloop_tmp++;
      }
    }
    fast_digitalWrite_HIGH(rowPin[i]);
  }
  return llkeylloop_tmp;
}
/////////////////////////////////////////////////////////////////
//キー押し込み
void key_press(int key_code){
  switch (key_code) {
    case MC_LC: Mouse.press(MOUSE_LEFT); break;
    case MC_RC: Mouse.press(MOUSE_RIGHT); break;
    case MC_MC: Mouse.press(MOUSE_MIDDLE); break;
    case MC_HU: Mouse.move(0, 0, +1);break;
    case MC_HD: Mouse.move(0, 0, -1);break;
    case CC_OSU: OSUkey_press();break;
    default: Keyboard.press(key_code);
  }
}
/////////////////////////////////////////////////////////////////
//キー押し込み解除
void key_release(int key_code){
  switch (key_code) {
    case MC_LC: Mouse.release(MOUSE_LEFT); break;
    case MC_RC: Mouse.release(MOUSE_RIGHT); break;
    case MC_MC: Mouse.release(MOUSE_MIDDLE); break;
    case MC_HU: Mouse.move(0, 0, +1);break;
    case MC_HD: Mouse.move(0, 0, -1);break;
    case CC_OSU: OSUkey_release();break;
    default: Keyboard.release(key_code);
  }
}
/////////////////////////////////////////////////////////////////
bool fast_digitalRead(byte pin){//（読み取り高速化関数）
 bool State;
  switch (register_num[0][pin]) {
    case 2:State = PINB & _BV(register_num[1][pin]);break;
    case 3:State = PINC & _BV(register_num[1][pin]);break;
    case 4:State = PIND & _BV(register_num[1][pin]);break;
    case 5:State = PINE & _BV(register_num[1][pin]);break;
    case 6:State = PINF & _BV(register_num[1][pin]);break;
  }
  return State;
}
/////////////////////////////////////////////////////////////////
void fast_digitalWrite_HIGH(byte pin){
  switch (register_num[0][pin]) {
    case 2:PORTB |= _BV(register_num[1][pin]);break;
    case 3:PORTC |= _BV(register_num[1][pin]);break;
    case 4:PORTD |= _BV(register_num[1][pin]);break;
    case 5:PORTE |= _BV(register_num[1][pin]);break;
    case 6:PORTF |= _BV(register_num[1][pin]);break;
  }
}
/////////////////////////////////////////////////////////////////
void fast_digitalWrite_LOW(byte pin){
  switch (register_num[0][pin]) {
    case 2:PORTB &= ~_BV(register_num[1][pin]);break;
    case 3:PORTC &= ~_BV(register_num[1][pin]);break;
    case 4:PORTD &= ~_BV(register_num[1][pin]);break;
    case 5:PORTE &= ~_BV(register_num[1][pin]);break;
    case 6:PORTF &= ~_BV(register_num[1][pin]);break;
  }
}
/////////////////////////////////////////////////////////////////
//マウス時間制御（X進行方向、Y進行方向、移動時間ミリ、待機時間ミクロ）
/*void Mouse_timer(int X_move, int Y_move, int index, int stop) {
  unsigned long time = millis();
  bool timer_loop = true;
  do {
    time = millis() - time;
    delayMicroseconds(stop);
    Mouse.move(X_move, Y_move, 0);
    if(time >= index)timer_loop = false;
  } while(timer_loop);
}*/
/////////////////////////////////////////////////////////////////
//OSUキー押し込み
void OSUkey_press(void){
  if (Key_OSUindex_in == 0) {
    Keyboard.release(KC_Z);
    Keyboard.press(KC_Z);
    Key_OSUindex_in = 1;
  }else{
    Keyboard.release(KC_X);
    Keyboard.press(KC_X);
    Key_OSUindex_in = 0;
  }
}
/////////////////////////////////////////////////////////////////
//OSUキー解除
void OSUkey_release(void){
  if (Key_OSUindex_out == 0) {
    Keyboard.release(KC_Z);
    Key_OSUindex_out = 1;
  }else{
    Keyboard.release(KC_X);
    Key_OSUindex_out = 0;
  }
}
/////////////////////////////////////////////////////////////////
//ASCII確認

/////////////////////////////////////////////////////////////////
//ASCII確認
/*void ASCII_check(void){
  while (!llkeylloop());//どれか一つキーが押されるまで待機
  for (byte i = 32; i <= 126; i++) {
    if( i != 96){
      loopTime();
      Keyboard.print(i);
      if(i < 100)Keyboard.write(32);
      if(i < 10)Keyboard.write(32);
      Keyboard.write(39);
      Keyboard.write(i);
      Keyboard.write(KC_MINS);
      Keyboard.write(KC_MINS);
      Keyboard.write(KC_MINS);
      Keyboard.press(KC_LSFT);
      Keyboard.write(i);
      Keyboard.release(KC_LSFT);
      Keyboard.write(176);
    }
  }
}
/////////////////////////////////////////////////////////////////
//キーコードシリアルプリント
void keyCodePrint(void){
  for (int i = 0; i < 135; i++) {
    char buf[4];
    for (byte j = 0 ; j < 4 ; j++){
      buf[j] = pgm_read_byte(keyCode[i] + j);
    }
    Serial.println(buf);
  }
}*/
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  byte i, j;
  for ( i = 0; i < rowNum; i++) { //列のピンをアウトプットに割り当てOUTPUT
    pinMode(rowPin[i], OUTPUT);
  }
  for ( i = 0; i < colNum; i++) { //行のピンをインプットに割り当て（プルアップ抵抗あり）INPUT_PULLUP
    pinMode(colPin[i], INPUT_PULLUP);
  }
  for ( i = 0; i < rowNum; i++) { //スイッチ状態を初期化
    for ( j = 0; j < colNum; j++) {
      currentState[i][j] = HIGH;
      beforeState[i][j] = HIGH;
      changeState[i][j] = HIGH;
    }
    digitalWrite(rowPin[i], HIGH);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  for (byte JS = 0 ; JS < 2 ; JS++) pinMode(stk_pins[JS], INPUT); //ジョイスティックピンをインプットに設定
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(115200); //シリアル通信を開始
  Serial1.begin(115200);
  Wire.begin();
  Serial.setTimeout(1);//シリアル通信でのタイムアウト設定
  for(int f = 0;;f++){//トリムに使う符号の要素数を記録する
    if(trimStr_serial[f] == '\0'){
      trimStr_serial_count = f+1;
      break;
    }
  }
  //trimStr_serial_count = Cstr_count(trimStr_serial);
  Serial.println(trimStr_serial_count);
  Keyboard.begin(); //キーボードHIDを開始
  Mouse.begin(); //マウスHIDを開始
  oled_X = u8g.getWidth();
  oled_Y = u8g.getHeight();
  key_BoxX = oled_X / rowNum;
  key_BoxY = oled_Y / colNum;

  keyMap_switch(0);
  u8g.firstPage();
  do {
    if(direction[0])u8g.setRot180();
    u8g.setFont(u8g_font_profont15r);
    u8g.drawStr( 44, 16, F("A0DBv2"));
    u8g.drawFrame(37, 1, 58, 20);
  } while ( u8g.nextPage() );
}
/////////////////////////////////
void loop() {
  String serial_str;
  bool loopReset = 1;
  while (loopReset) {
    loopTime();
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //シリアルループ
    char buf;
    if((buf = Serial.read()) != -1){
      if (String(buf) == String(";")){
        Serial.println("");
        loopReset = 0;
      }else{
        serial_str += buf;
        Serial.print(buf);
      }
    }
    if (!loopReset){//シリアル終端文字が入力されると必然的にループリセットがかかるのでそれを条件に使用

      Keyboard.releaseAll();
      for (byte i = 0; i < rowNum; i++) {//キーボードの状態をリセット
        for (byte j = 0; j < colNum; j++) {
          beforeState[i][j] = HIGH;
          currentState[i][j] = HIGH;
        }
        fast_digitalWrite_HIGH(rowPin[i]);
      }

      //serial_str = Serial.readStringUntil(';');//PCから文字列を受信。終端文字（;）かタイムアウトで受信終了。
      serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。

      for(byte i = 0; i < trimStr_serial_count; i++){//文字列の種類の数だけループ。
        String str_index = String(trimStr_serial[i]);//指定の配列をcharからstringに変換。
        int str_pos = serial_str.indexOf(str_index);//シリアルの文字配列から指定の文字があるか検索。ある場合位置を出力。

        if (str_pos > -1) {//上記の検索に適合文字があった場合実行される。
          serial_str.remove(str_pos,str_index.length());//シリアルから送られてきた符号を消去。データを使いやすくする。
          serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。
          switch (i) {
            case 0:keyMap_switch(serial_str.toInt());break;                                        //キーマップ切り替え
            case 1:Serial.println(serial_str);break;                                               //受信したデータをそのまま返す
            case 2:OLED_drawStr(0, 12, serial_str.c_str(), 0);break;                               //通常サイズの文字を表示
            case 3:OLED_drawStr(0, 12, serial_str.c_str(), 1);break;                               //倍サイズの文字を表示
            case 4:u8g.firstPage();do {u8g.drawBox(0, 0, 128, 32);} while ( u8g.nextPage() );break;//OLEDをすべて白光
            case 5:timeCount = serial_str.toInt();break;                                          //プログラムが一周にかかる時間を出力
            //case 6:ASCII_check();break;                                                            //通常のキーの一覧を出力
            case 7:Serial.println(serial_str.toInt(),BIN);break;                                     //受信したデータの2進数を返す
            //case 8:keyCodePrint();break;                                                           //シリアルにキーコード符号を出力
            case 9:
            byte keyMap_num;                                                                //キーマップをシリアル経由で書き換え
            Serial.println(F("RW##########################################################"));
            Serial.println(F("格納するキーを押してください"));

            /////////////////////////////////////最初に格納する番号を取得する
            bool Loop = true;
            //Serial.println(serial_str);
            while (llkeylloop());
            do {
              if (Serial.available() > 0){//PCからシリアルデータが受信されていないか監視
                String keyMap_num_str = Serial.readStringUntil(';');//PCから文字列を受信。終端文字（;）かタイムアウトで受信終了。
                keyMap_num_str.trim();//送られてきた文字列の前後の余計な空白を消去。
                keyMap_num = keyMap_num_str.toInt();
                Loop = false;
              }else{
                for (byte i = 0; i < rowNum; i++) {//格納する番号をシリアルかキースイッチから取得する。
                  fast_digitalWrite_LOW(rowPin[i]);
                  for (byte j = 0; j < colNum; j++) {
                    if(fast_digitalRead(colPin[j]) == LOW){
                      bool keyblock = LOW;
                      keyMap_num = i*colNum+j;
                      do {
                        keyblock = digitalRead(colPin[j]);
                      }while (keyblock == LOW);
                      Loop = false;
                    }
                  }
                  fast_digitalWrite_HIGH(rowPin[i]);
                }
              }
            } while(Loop);
            Serial.print(F("格納番号："));
            Serial.println(keyMap_num);
            Serial.println(F("解析中"));
            /////////////////////////////////////
            Loop = true;
            byte tmpMap_row = 0;
            byte tmpMap_col = 0;
            byte tmpMap_din = 0;
            byte matrixNum = 0;
            const byte trimStr_KR_count = 11;//符号の種類の数
            const char* trimStr_KR[] =//どういう情報が送られてきたか判断するための符号
            //0      1      2      3      4      5      6      7      8      9     10
            {"K{"  ,"J{"  ,"{"   ,"KC_" ,"MC_" ,"LAY_","CC_" ,","   ,"},"  ,"}."  ,"}"   };
            while (llkeylloop());
            do {
              for(byte i = 0; i < trimStr_KR_count; i++){//文字列の種類の数だけループ
                serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。
                String str_tmp = String(trimStr_KR[i]);//指定の配列をcharからstringに変換。
                int RWstr_pos = serial_str.indexOf(str_tmp);//シリアルの文字配列から指定の文字があるか検索。ある場合位置を出力。

                if (RWstr_pos == 0) {//上記の検索に適合文字があった場合実行される。
                  serial_str.remove(RWstr_pos,str_tmp.length());//シリアルから送られてきた符号を消去。データを使いやすくする。
                  serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。
                  byte codeMode_Num = 0;
                  switch (i) {
                    case 0: matrixNum = 1;tmpMap_din = 0;tmpMap_row = 0;tmpMap_col = 0;Serial.print(F("K{"));break;// K{
                    case 1: matrixNum = 2;tmpMap_din = 0;tmpMap_row = 0;tmpMap_col = 0;Serial.print(F("J{"));break;// J{
                    case 2: Serial.print(F(" {"));break;// {
                    case 3: codeMode_Num = 1;Serial.print(F("KC_"));break; //0x0000
                    case 4: codeMode_Num = 2;Serial.print(F("MC_"));break; //0x0100
                    case 5: codeMode_Num = 3;Serial.print(F("LAY_"));break;//0x0200
                    case 6: codeMode_Num = 4;Serial.print(F("CC_"));break; //0x0300
                    case 7: tmpMap_col++;Serial.print(F(","));break;// ,
                    case 8: tmpMap_row++;tmpMap_col = 0;Serial.println(F("},"));break;// },
                    case 9: tmpMap_din++;tmpMap_row = 0;tmpMap_col = 0;Serial.println(F("}."));Serial.println(F(""));break;// }.
                    case 10:Loop = 0;Serial.println(F("}"));break;// }
                  }
                  if(codeMode_Num){
                    int tmpPos1 = -1;
                    byte tmpi = 7;//コンマがの位置
                    ///////↓キーコードの長さを調べる
                    while (tmpPos1 == -1 && tmpi < trimStr_KR_count) {
                      String tmpstr1 = String(trimStr_KR[tmpi]);//指定の配列をcharからstringに変換。
                      serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。
                      tmpPos1 = serial_str.indexOf(tmpstr1);//トリムKRから指定文字を検索。見つかればループ解除
                      tmpi += 1;
                    }
                    ///////↓キーコードの部分を切り取る
                    if (tmpPos1 > 4) tmpPos1 = 4;//キーコードのカット幅が4文字以上なら強制的に4文字に設定
                    String strKey_code = serial_str.substring(0,tmpPos1);//キーコードを抽出
                    serial_str.remove(0,tmpPos1);//親元（serial_ser）のキーコードを消去する
                    strKey_code.trim();//余分な空白を消去

                    ///////↓受信したキーコードとASCIIを照合し合致した場合数値を記録
                    for (int codeNum = 0; codeNum < 219; codeNum++) {//シリアルからのキーコードと番号を照合。合致した場合マップに格納。
                      char keyCode_buf[4];

                      for (byte chrNum = 0 ; chrNum < 5 ; chrNum++){//参照するキーコードをflashからramにコピー
                        switch (codeMode_Num) {
                          case 1:keyCode_buf[chrNum] = pgm_read_byte(keyCode[codeNum] + chrNum);break;
                          case 2:keyCode_buf[chrNum] = pgm_read_byte(mouseCode[codeNum] + chrNum);break;
                          case 3:keyCode_buf[chrNum] = pgm_read_byte(layerCode[codeNum] + chrNum);break;
                          case 4:keyCode_buf[chrNum] = pgm_read_byte(customCode[codeNum] + chrNum);break;
                        }
                      }
                      //if(codeNum%10==0)Serial.print(F("x"));

                      if(strKey_code == String(keyCode_buf)){//キーコードが一致した場合
                        Serial.print(keyCode_buf);
                        if(strKey_code.length() < 4)Serial.print(F(" "));
                        if(strKey_code.length() < 3)Serial.print(F(" "));
                        if(strKey_code.length() < 2)Serial.print(F(" "));
                        switch (matrixNum) {
                          case 1:keyMap_temp[tmpMap_din][tmpMap_row][tmpMap_col] = codeNum + 0x100 * (codeMode_Num-1);break;
                          case 2:JSkeyMap_temp[tmpMap_row][tmpMap_col] = codeNum + 0x100 * (codeMode_Num-1);break;
                        }
                        break;
                      }else if (strKey_code == String("____")) {
                        Serial.print(F("____"));
                        switch (matrixNum) {
                          case 1:keyMap_temp[tmpMap_din][tmpMap_row][tmpMap_col] = 0x00;break;
                          case 2:JSkeyMap_temp[tmpMap_row][tmpMap_col] = 0x00;break;
                        }
                        break;
                      }
                    }
                  }
                  break;
                }
              }
            } while(Loop);
            Serial.println(F("書き込み中"));
            KMeepromWrite(keyMap_num);
            Serial.println(F("完了"));
            Serial.println(F("############################################################"));
            break;//switch
          }
          break;
        }
      }
    }
    /////////////////////////////////////↓キー検出
    for (byte i = 0; i < rowNum; i++) {
      fast_digitalWrite_LOW(rowPin[i]);

      for (byte j = 0; j < colNum; j++) {
        beforeState[i][j] = currentState[i][j];
        currentState[i][j] = fast_digitalRead(colPin[j]);
      }
      fast_digitalWrite_HIGH(rowPin[i]);
    }

    for (byte JS = 0 ; JS < 2 ; JS++) {
      vr[JS] = vr[JS] * 0.9 + (analogRead(stk_pins[JS]) - 1023 / 2) * 0.1; //生の値を半分にし、上下±で表現するようにする
      char deg = (vr[JS] > 0) ? 1 : -1; //一定範囲の値は０に書き換える（補正範囲）
      pos[JS] = (abs(vr[JS]) < VR_IDLE) ? 0 : vr[JS] - (VR_IDLE * deg); //一定範囲の値は０に書き換える（補正範囲）
      pos[JS] = constrain(pos[JS], VRNG * -1, VRNG);  //生の値の最小値と最大値の絶対値が異なるのでそろえる
    }
    if (direction[1]) {
      pos[0] *= -1;
      pos[1] *= -1;
    }else{
      pos[1] *= -1;
    }
    ////////////////////////////
    currentJS[0] = false;
    currentJS[1] = false;
    currentJS[2] = false;
    currentJS[3] = false;
    ////↓ジョイスティックの状態を記録
    if (pos[1] > JS_Dead_zone && pos[0] < JS_Diagonal_Dead_zone && pos[0] > -JS_Diagonal_Dead_zone) { //上
      currentJS[0] = true;
      //Serial.print("↑---");
    } else if (pos[1] < -JS_Dead_zone && pos[0] < JS_Diagonal_Dead_zone && pos[0] > -JS_Diagonal_Dead_zone) { //下
      currentJS[2] = true;
      //Serial.print("↓---");
    } else if (pos[0] > JS_Dead_zone && pos[1] < JS_Diagonal_Dead_zone && pos[1] > -JS_Diagonal_Dead_zone) { //左
      currentJS[3] = true;
      //Serial.print("←---");
    } else if (pos[0] < -JS_Dead_zone && pos[1] < JS_Diagonal_Dead_zone && pos[1] > -JS_Diagonal_Dead_zone) { //右
      currentJS[1] = true;
      //Serial.print("→---");
    } else if (pos[1] >= JS_Diagonal_Dead_zone && pos[0] >= JS_Diagonal_Dead_zone) { //上斜め左
      currentJS[0] = true;
      currentJS[3] = true;
      //Serial.print("←↑---");
    } else if (pos[1] >= JS_Diagonal_Dead_zone && pos[0] <= -JS_Diagonal_Dead_zone) { //上斜め右
      currentJS[0] = true;
      currentJS[1] = true;
      //Serial.print("↑→---");
    } else if (pos[1] <= -JS_Diagonal_Dead_zone && pos[0] >= JS_Diagonal_Dead_zone) { //下斜め左
      currentJS[2] = true;
      currentJS[3] = true;
      //Serial.print("←↓---");
    } else if (pos[1] <= -JS_Diagonal_Dead_zone && pos[0] <= -JS_Diagonal_Dead_zone) { //下斜め右
      currentJS[1] = true;
      currentJS[2] = true;
      //Serial.print("↓→---");
    }
    //if(Serial){////////////////////////////////ホスト処理
      switch (Switch_KMode) {
        case 1 : /////////////////////////////////////////////////////////キーボードモード
        if (currentState[Switch_key[0][0]][Switch_key[0][1]] == LOW &&//キーマップ切り替え呼び出し
            currentState[Switch_key[1][0]][Switch_key[1][1]] == LOW &&
            currentState[Switch_key[2][0]][Switch_key[2][1]] == LOW) {
          for (int a = 0; a < 3; a++) {
            currentState[Switch_key[a][0]][Switch_key[a][1]] = HIGH;
            Keyboard.release(keyMap[direction[0]][Switch_key[a][0]][Switch_key[a][1]]);
            //ser1_send = 0 << 7 | Switch_key[a][1] << 3 | Switch_key[a][0];//0 0000 000
            //Serial1.write(ser1_send);
          }
          Serial.println(F("切り替えモード"));
          bool Loop_in = true;
          do {//切り替えスイッチがまだ押されていたらここでせき止める
            for (byte z = 0; z < rowNum; z++) {
              digitalWrite( rowPin[z], LOW );
              for (byte x = 0; x < colNum; x++) {
                changeState[z][x] = digitalRead(colPin[x]);
              }
              digitalWrite( rowPin[z], HIGH );
            }
            if ( changeState[Switch_key[0][0]][Switch_key[0][1]] == HIGH &&
                 changeState[Switch_key[1][0]][Switch_key[1][1]] == HIGH &&
                 changeState[Switch_key[2][0]][Switch_key[2][1]] == HIGH )Loop_in = false;
          } while (Loop_in);
          switchAnimation();
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        } else {
          for (byte i = 0; i < rowNum; i++) {
            for (byte j = 0; j < colNum; j++) {
              if ( currentState[i][j] != beforeState[i][j] ) { //前回とキーの状態が違えば実行
                if ( currentState[i][j] == LOW) { //スイッチの状態を参照し、押されている場合実行
                  key_press(keyMap[direction[0]][i][j]);//キー押し込み
                  ser1_send_key = i << 5 | j << 2 | 1 << 1 | 1;//000 000 0 0
                }else{ //スイッチの状態を参照し、離されている場合実行
                  key_release(keyMap[direction[0]][i][j]);//キー解除
                  ser1_send_key = i << 5 | j << 2 | 0 << 1 | 1;//000 000 0 0
                }

                u8g.firstPage();
                do {/////////////////////////////////↓oled常時処理
                  for (byte i = 0; i < rowNum; i++) {
                    for (byte j = 0; j < colNum; j++) {
                      if(currentState[i][j] == LOW){//落
                        if(direction[1]){
                          u8g.drawBox((key_BoxX*(rowNum-1-i)), (key_BoxY*j), key_BoxX, key_BoxY);
                        }else{
                          u8g.drawBox((key_BoxX*i), (key_BoxY*j), key_BoxX, key_BoxY);
                        }
                      /*}else{
                        if(direction[1]){
                          u8g.drawFrame((key_BoxX*(rowNum-1-i)), (key_BoxY*j), key_BoxX, key_BoxY);
                        }else{
                          u8g.drawFrame((key_BoxX*i), (key_BoxY*j), key_BoxX, key_BoxY);
                        }*/
                      }
                    }
                  }
                } while ( u8g.nextPage() );

                /*Serial1.write(ser1_send_key);
                Serial.print(i);Serial.print(',');
                Serial.print(j);Serial.print(',');
                Serial.println(keyMap[direction[0]][i][j],HEX);//Serial.print(',');*/
              }
            }
          }
        }
        //////////////////////////////////////////
        if (JSkeyMap[0] == MC_P) {
          for (int i = 0; i < 2; i++) {
            if (pos[i] != 0) {
              if (pos[i] >= PDz || pos[i] <= -PDz) {
                M_point[i] = pos[i] / 220;
                if (i == 0)Mouse.move(M_point[0], 0 , 0);
                if (i == 1)Mouse.move(0, M_point[1], 0);
              } else {
                M_PP[i] = map( pos[i], 0, PDz - 1, 3, 1);
                if (MTime[i] + M_PP[i] < millis()) {
                  if (i == 0){
                    if (pos[i] > 0)Mouse.move(1, 0 , 0);
                    if (pos[i] < 0)Mouse.move(-1, 0 , 0);
                  }else if (i == 1){
                    if (pos[i] < 1)Mouse.move(0 , -1 , 0);
                    if (pos[i] > 1)Mouse.move(0 , 1 , 0);
                  }
                  MTime[i] = millis();
                }
              }
            }
          }
        } else {
          for (int i = 0; i < 4; i++) {
            if (beforeJS[i] != currentJS[i]) {
              if (currentJS[i] == true) {
                key_press(JSkeyMap[direction[0]][i]);
                ser1_send_joy = 0b0000 << 4 | i << 2 | 1 << 1 | 0;//0000 00 0 0
              } else if (currentJS[i] == false) {
                key_release(JSkeyMap[direction[0]][i]);
                ser1_send_joy = 0b0000 << 4 | i << 2 | 0 << 1 | 0;//0000 00 0 0
              }
              Serial1.write(ser1_send_joy);
            }
            beforeJS[i] = currentJS[i];
          }
        }
        break;
      }/////////////////////////////////////////////ser1受信処理↓
      //////////////////// mode  joy  keypush?  1:key?0:mode? | row  col keypush? 0:joy?1:key?
      //////////////////// 0000   00      0           0       | 000  000    0          1
      byte ser1_count = Serial1.available();//受信数を記録
      if(ser1_count){//１つでも受信しているなら実行
        for(byte i = 0; i < ser1_count; i++){//複数ある場合繰り返して実行
          ser1_recv = Serial1.read();
          if(ser1_recv & 1){//キー座標処理
            ser1_keyState = ser1_recv >> 1 & 0b00000001;
            ser1_col = ser1_recv >> 2 & 0b00000111;
            ser1_row = ser1_recv >> 5 & 0b00000111;

            if(ser1_keyState){
              key_press(keyMap[direction[1]][ser1_row][ser1_col]);
            }else{
              key_release(keyMap[direction[1]][ser1_row][ser1_col]);
            }
          }else{//キー状態、ジョイスティック、モード処理
            ser1_joyState = ser1_recv >> 1 & 0b00000001;
            ser1_joynum = ser1_recv >> 2 & 0b00000011;
            //Serial.println(ser1_recv,BIN);
            if(ser1_joyState){
              key_press(JSkeyMap[direction[1]][ser1_joynum]);
            }else{
              key_release(JSkeyMap[direction[1]][ser1_joynum]);
            }
          }
          //Serial.println(ser1_recv,BIN);
        }
      }
    /*}else{///////////////////////////////////////////////////ゲスト処理
      switch (Switch_KMode) {
        case 1 :
        for (byte i = 0; i < rowNum; i++) {
          for (byte j = 0; j < colNum; j++) {
            if ( currentState[i][j] != beforeState[i][j] ) { //前回とキーの状態が違えば実行
              if ( currentState[i][j] == LOW) { //スイッチの状態を参照し、押されている場合実行
                ser1_send_key = i << 5 | j << 2 | 1 << 1 | 1;//000 000 0 0
              }else{ //スイッチの状態を参照し、離されている場合実行
                ser1_send_key = i << 5 | j << 2 | 0 << 1 | 1;//000 000 0 0
              }
              Serial1.write(ser1_send_key);
            }
          }
        }
        for (int i = 0; i < 4; i++) {
          if (beforeJS[i] != currentJS[i]) {
            if (currentJS[i]) {
              ser1_send_joy = 0b0000 << 4 | i << 2 | 1 << 1 | 0;//0000 00 0 0
            } else {
              ser1_send_joy = 0b0000 << 4 | i << 2 | 0 << 1 | 0;//0000 00 0 0
            }
            Serial1.write(ser1_send_joy);
          }
          beforeJS[i] = currentJS[i];
        }
        break;
      }
    }*/
  }
}

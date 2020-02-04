#ifndef INCLUDED_fastIO_h_
#define INCLUDED_fastIO_h_
#include <Arduino.h>
static const byte register_num[2][22] = {//１段目はポート番号(Aが最初、1から始まる)(0は無効)、２段目はビット番号
///0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21
  {4, 4, 4, 4, 4, 3, 4, 5, 2, 2, 2, 0, 0, 0, 2, 2, 2, 0, 6, 6, 6, 6,},
  {2, 3, 1, 0, 4, 6, 7, 6, 4, 5, 6, 0, 0, 0, 3, 1, 2, 0, 7, 6, 5, 4,},
};
/////////////////////////////////////////////////////////////////
bool fast_digitalRead(byte pin){//（読み取り高速化関数）
  switch (register_num[0][pin]) {
    case 2:return PINB & _BV(register_num[1][pin]);
    case 3:return PINC & _BV(register_num[1][pin]);
    case 4:return PIND & _BV(register_num[1][pin]);
    case 5:return PINE & _BV(register_num[1][pin]);
    case 6:return PINF & _BV(register_num[1][pin]);
  }
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
#endif

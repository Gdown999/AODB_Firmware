#ifndef INCLUDED_Keydefine_h_

  #define INCLUDED_Keydefine_h_

  #define NONE    0x00
  #define _______ 0x00
  #define KC_____ 0x00

  #define MC_LC  0x100
  #define MC_RC  0x101
  #define MC_MC  0x102
  #define MC_HU  0x103
  #define MC_HD  0x104
  #define MC_P   0x105

  #define LAY_00  0x200
  #define LAY_01  0x201
  #define LAY_02  0x202
  #define LAY_03  0x203

  #define CC_OSU 0x300
//over 0xDA
  #define KC_ENT  0xB0
  #define KC_ESC  0xB1
  #define KC_BSPC 0xB2
  #define KC_DEL  0xD4
  #define KC_TAB  0xB3
  #define KC_CAPS 0xC1
  #define KC_LCTL 0x80
  #define KC_LSFT 0x81
  #define KC_LALT 0x82
  #define KC_LGUI 0x83
  #define KC_RCTL 0x84
  #define KC_RSFT 0x85
  #define KC_RALT 0x86
  #define KC_RGUI 0x87

  #define KC_PGUP 0xD3
  #define KC_PGDN 0xD6
  #define KC_HOME 0xD2
  #define KC_END  0xD5
  #define KC_LEFT 0xD8
  #define KC_RGHT 0xD7
  #define KC_UP   0xDA
  #define KC_DOWN 0xD9

  #define KC_0  0x30
  #define KC_1  0x31
  #define KC_2  0x32
  #define KC_3  0x33
  #define KC_4  0x34
  #define KC_5  0x35
  #define KC_6  0x36
  #define KC_7  0x37
  #define KC_8  0x38
  #define KC_9  0x39

  #define KC_COLN 0x3A
  #define KC_EXLM 0x21
  #define KC_DQUO 0x22
  #define KC_AT   0x40
  #define KC_HASH 0x23
  #define KC_DLR  0x24
  #define KC_PERC 0x25
  #define KC_CIRC 0x5E
  #define KC_AMPR 0x26
  #define KC_ASTR 0x2A
  #define KC_LPRN 0x28
  #define KC_RPRN 0x29
  #define KC_LABK 0x3C
  #define KC_RABK 0x3E
  #define KC_QUES 0x3F

  #define KC_MINS 0x2D
  #define KC_EQL  0x3D
  #define KC_SPC  0x20
  #define KC_LBRC 0x5B
  #define KC_RBRC 0x5D
  #define KC_LCBR 0x7B
  #define KC_RCBR 0x7D
  #define KC_BSLS 0x5C
  #define KC_SCLN 0x3B
  #define KC_QUOT 0x27
  #define KC_GRV  0x60
  #define KC_COMM 0x2C
  #define KC_DOT  0x2E
  #define KC_SLSH 0x2F
  #define KC_ANBR 0x5F
  #define KC_PIPE 0x7C

  #define KC_A 0x61
  #define KC_B 0x62
  #define KC_C 0x63
  #define KC_D 0x64
  #define KC_E 0x65
  #define KC_F 0x66
  #define KC_G 0x67
  #define KC_H 0x68
  #define KC_I 0x69
  #define KC_J 0x6A
  #define KC_K 0x6B
  #define KC_L 0x6C
  #define KC_M 0x6D
  #define KC_N 0x6E
  #define KC_O 0x6F
  #define KC_P 0x70
  #define KC_Q 0x71
  #define KC_R 0x72
  #define KC_S 0x73
  #define KC_T 0x74
  #define KC_U 0x75
  #define KC_V 0x76
  #define KC_W 0x77
  #define KC_X 0x78
  #define KC_Y 0x79
  #define KC_Z 0x7A

  /*const char* const keyCode[] PROGMEM = {
    //0      1      2      3      4      5      6      7      8      9     10     11     12     13     14     15     16     17     18     19
    "NUL" ,"SOH" ,"STX" ,"ETX" ,"EOT" ,"ENQ" ,"ACK" ,"BEL" ,"BS"  ,"TAB" ,"LF"  ,"VT"  ,"FF"  ,"CR"  ,"SO"  ,"SI"  ,"DLE" ,"DC1" ,"DC2" ,"DC3" ,
    "DC4" ,"NAK" ,"SYN" ,"ETB" ,"CAN" ,"EM"  ,"SUB" ,"ESC" ,"FS"  ,"GS"  ,"RS"  ,"US"  ,"SPC" ,"EXLM","DQUO","HASH","DLR" ,"PERC","AMPR","QUOT",
    "LPRN","RPRN","ASTR","PLUS","COMM","MINS","DOT" ,"SLSH","0"   ,"1"   ,"2"   ,"3"   ,"4"   ,"5"   ,"6"   ,"7"   ,"8"   ,"9"   ,"COLN","SCLN",
    "LABK","EQL" ,"RABK","QUES","AT"  ,"SFTA","SFTB","SFTC","SFTD","SFTE","SFTF","SFTG","SFTH","SFTI","SFTJ","SFTK","SFTL","SFTM","SFTN","SFTO",
    "SFTP","SFTQ","SFTR","SFTS","SFTT","SFTU","SFTV","SFTW","SFTX","SFTY","SFTZ","LBRC","BSLS","RBRC","CIRC","ANBR","GRV" ,"A"   ,"B"   ,"C"   ,
    "D"   ,"E"   ,"F"   ,"G"   ,"H"   ,"I"   ,"J"   ,"K"   ,"L"   ,"M"   ,"N"   ,"O"   ,"P"   ,"Q"   ,"R"   ,"S"   ,"T"   ,"U"   ,"V"   ,"W"   ,
    "X"   ,"Y"   ,"Z"   ,"LCBR","PIPE","RCBR",""    ,"DEL" ,"LCTL","LSFT","LALT","LGUI","RCTL","RSFT","RALT","RGUI",""    ,""    ,""    ,""    ,
    "","","","","","","","","","","","","","","","","","","","",
    "","","","","","","","","","","","","","","","","","","","",
    "","","","","","","","","","","","","","","","","","","","",
    "","","","","","","","","","","","","","","","","","","","",
    "","","","","","","","","","","","","","","","",
  };
  const char* const keyCode_prg[] PROGMEM = {
    // 0            1            2            3            4            5            6            7            8            9
    keyCode[0],  keyCode[1],  keyCode[2],  keyCode[3],  keyCode[4],  keyCode[5],  keyCode[6],  keyCode[7],  keyCode[8],  keyCode[9],
    keyCode[10], keyCode[11], keyCode[12], keyCode[13], keyCode[14], keyCode[15], keyCode[16], keyCode[17], keyCode[18], keyCode[19],
    keyCode[20], keyCode[21], keyCode[22], keyCode[23], keyCode[24], keyCode[25], keyCode[26], keyCode[27], keyCode[28], keyCode[29],
    keyCode[30], keyCode[31], keyCode[32], keyCode[33], keyCode[34], keyCode[35], keyCode[36], keyCode[37], keyCode[38], keyCode[39],
    keyCode[40], keyCode[41], keyCode[42], keyCode[43], keyCode[44], keyCode[45], keyCode[46], keyCode[47], keyCode[48], keyCode[49],
    keyCode[50], keyCode[51], keyCode[52], keyCode[53], keyCode[54], keyCode[55], keyCode[56], keyCode[57], keyCode[58], keyCode[59],
    keyCode[60], keyCode[61], keyCode[62], keyCode[63], keyCode[64], keyCode[65], keyCode[66], keyCode[67], keyCode[68], keyCode[69],
    keyCode[70], keyCode[71], keyCode[72], keyCode[73], keyCode[74], keyCode[75], keyCode[76], keyCode[77], keyCode[78], keyCode[79],
    keyCode[80], keyCode[81], keyCode[82], keyCode[83], keyCode[84], keyCode[85], keyCode[86], keyCode[87], keyCode[88], keyCode[89],
    keyCode[90], keyCode[91], keyCode[92], keyCode[93], keyCode[94], keyCode[95], keyCode[96], keyCode[97], keyCode[98], keyCode[99],
    keyCode[100],keyCode[101],keyCode[102],keyCode[103],keyCode[104],keyCode[105],keyCode[106],keyCode[107],keyCode[108],keyCode[109],
    keyCode[110],keyCode[111],keyCode[112],keyCode[113],keyCode[114],keyCode[115],keyCode[116],keyCode[117],keyCode[118],keyCode[119],
    keyCode[120],keyCode[121],keyCode[122],keyCode[123],keyCode[124],keyCode[125],keyCode[126],keyCode[127],keyCode[128],keyCode[129],
    keyCode[130],keyCode[131],keyCode[132],keyCode[133],keyCode[134],keyCode[135],keyCode[136],keyCode[137],keyCode[138],keyCode[139],
    keyCode[140],keyCode[141],keyCode[142],keyCode[143],keyCode[144],keyCode[145],keyCode[146],keyCode[147],keyCode[148],keyCode[149],
    keyCode[150],keyCode[151],keyCode[152],keyCode[153],keyCode[154],keyCode[155],keyCode[156],keyCode[157],keyCode[158],keyCode[159],
  };*/
  /////////////////////////////////////////////////////////////////
  /*/シリアル経由キーマップ書き込み関数
  void SKRW(void){
    byte keyMap_num;                                                                //キーマップをシリアル経由で書き換え
    Serial.println(F("格納するキーを押してください"));

    /////////////////////////////////////最初に格納する番号を取得する
    bool Loop = true;
    Serial.println(serial_str);
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
    Serial.println(keyMap_num);
    /////////////////////////////////////
    Loop = true;
    byte tmpMap_row = 0;
    byte tmpMap_col = 0;
    byte tmpMap_din = 0;
    const byte trimStr_KR_count = 6;//符号の種類の数
    const char* trimStr_KR[] =//どういう情報が送られてきたか判断するための符号
     //  0         1       2        3       4       5
    {  "{"  ,  "KC_"  ,  ","  ,  "},"  ,  "}."  ,  "}"  };
    while (llkeylloop());
    do {
      for(byte i = 0; i < trimStr_KR_count; i++){//文字列の種類の数だけループ。
        serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。
        String str_tmp = String(trimStr_KR[i]);//指定の配列をcharからstringに変換。
        int RWstr_pos = serial_str.indexOf(str_tmp);//シリアルの文字配列から指定の文字があるか検索。ある場合位置を出力。
        //Serial.println(F("4"));
        //Serial.println(i);
        //Serial.println(RWstr_pos);
        Serial.println(RWstr_pos);
        if (RWstr_pos == 0) {//上記の検索に適合文字があった場合実行される。
          serial_str.remove(RWstr_pos,str_tmp.length());//シリアルから送られてきた符号を消去。データを使いやすくする。
          serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。
          Serial.print(F("1"));
          switch (i) {
            case 0:Serial.print(F("{"));break;// {
            case 2:tmpMap_col++;Serial.print(F(","));break;// ,
            case 3:tmpMap_row++;tmpMap_col = 0;Serial.println(F("},"));break;// },
            case 4:tmpMap_din++;tmpMap_row = 0;tmpMap_col = 0;Serial.println(F("}."));Serial.println(F(""));break;// }.
            case 5:Loop = 0;Serial.println(F("}"));break;// }
            case 1://KC_
            /*先頭から端末符号を探す。4文字以内で見つかっていればカット。
              見つかっていなければ先頭4文字をカット。*/
            /*Serial.print(F("KC_"));
            int tmpPos1 = -1;
            byte tmpi = 2;
            Serial.print(F("2"));
            while (tmpPos1 == -1 || tmpi <= 5) {
              String tmpstr1 = String(trimStr_KR[tmpi]);//指定の配列をcharからstringに変換。
              serial_str.trim();//送られてきた文字列の前後の余計な空白を消去。
              tmpPos1 = serial_str.indexOf(tmpstr1);//トリムKRから指定文字を2番から4番まで検索。見つかればループ解除
              tmpi += 1;
              Serial.print(tmpi);
            }

            if (tmpPos1 > 4) tmpPos1 = 4;//キーコードのカット幅が4文字以上なら強制的に4文字に設定
            String strKey_code = serial_str.substring(0,tmpPos1);//キーコードを抽出
            serial_str.remove(0,tmpPos1);//シリアルのキーコード部分は読み取ったので消去する
            strKey_code.trim();//余分な空白を消去
            Serial.print(F("3"));

            for (int codeNum = 0; codeNum < 219; codeNum++) {//シリアルからのキーコードと番号を照合。合致した場合マップに格納。
              char keyCode_buf[4];
              delay(1);
              Serial.println(codeNum);

              for (byte chrNum = 0 ; chrNum < 5 ; chrNum++){//参照するキーコードをflashからramにコピー
                keyCode_buf[chrNum] = pgm_read_byte(keyCode[codeNum] + chrNum);
              }
              //if(codeNum%10==0)Serial.print(F("x"));

              if(strKey_code == String(keyCode_buf)){
                Serial.print(keyCode_buf);
                //if(strKey_code.length() < 4)Serial.print(F(" "));
                //if(strKey_code.length() < 3)Serial.print(F(" "));
                //if(strKey_code.length() < 2)Serial.print(F(" "));
                keyMap_temp[tmpMap_din][tmpMap_row][tmpMap_col] = codeNum;
                break;
              }else if (codeNum == 218) {
                Serial.print(F("_"));
                Serial.print(F("_"));
                Serial.print(F("_"));
                Serial.print(F("_"));
              }
            }
            break;
          }
          break;
        }
      }
      Serial.println("");
      if(llkeylloop())Loop = 0;
    } while(Loop);
    keyMap_Rewrite(keyMap_temp, JSkeyMap_MOUSE, keyMap_OLED[0]);
    Serial.println(F("fin"));
  }*/
#endif

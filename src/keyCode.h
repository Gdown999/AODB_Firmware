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

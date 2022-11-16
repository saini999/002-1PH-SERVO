#include <EEPROM.h>
#include <BlockNot.h> //https://github.com/EasyG0ing1/BlockNot
#include "SevSeg.h" //https://github.com/sparkfun/SevSeg


SevSeg display1;

//BlockNot screen(2, SECONDS);
BlockNot refresh(1, SECONDS);
bool setupm = false;
int IHV;
int ILV;
int OHV;
int OLV;
int SETV;
int OVL;
int TON;
int TOFF;
int DIFF;
int enc;
const int ok = A0;
const int plus = A1;
const int minus = A2;
//const int setupPin = A3;
const int inVolt = A3;
const int outVolt = A4;
const int current = A5;
const int motor0Fwd = 0;
const int motor0Rev = 1;
int encMenu;
//int encMenu = 0;

bool okold = false;
bool plusold = false;
bool minusold = false;


void setup() {
setupDisplay();
setIN(ok);
setIN(plus);
setIN(minus);
//setIN(setupPin);
setIN(inVolt);
setIN(outVolt);
setIN(current);
setOUT(motor0Fwd);
setOUT(motor0Rev);
IHV = 2 * EEPROM.read(0);
ILV = 2 * EEPROM.read(1);
OHV = 2 * EEPROM.read(2);
OLV = 2 * EEPROM.read(3);
SETV = 2 * EEPROM.read(4);
OVL = EEPROM.read(5);
TON = EEPROM.read(6);
TOFF = EEPROM.read(7);
DIFF = EEPROM.read(8);


//attachInterrupt(A3, encmenuup, RISING);
}
bool switched = false;
bool mode = false;
void loop() {
  checkok();
  checkplus();
  checkminus();
  if(mode){
    runSetup();
  } else {
    runNormal();
  }
  if(read(ok) && read(plus) && read(minus) && switched == false){
    mode = !mode;
    switched = true;
    encMenu = 0;
  }
  if(!read(ok) && !read(plus) && !read(minus) && switched == true){
    switched = false;
  }
}
bool inputVok() {
  if(IV() > ILV && IV() < IHV){
    return true;
  } else {
    return false;
  }
}
bool outputVok() {
  if(OV() > OLV && OV() < OHV){
    return true;
  } else {
    return false;
  }
}
bool currentok() {
  if(amp() < OVL){
    return true;
  } else {
    return false;
  }
}

bool diffcheck() {
  int dif = SETV - OV();
  if(dif < 0){
    dif = dif * -1;
  }
  if(dif > DIFF){
    return true;
  } else {
    return false;
  }
}

void runNormal() {
  if(OV() < SETV && diffcheck() && inputVok() && currentok()){
    digitalWrite(motor0Fwd, HIGH);
  } else {
    digitalWrite(motor0Fwd, LOW);
  }
  if(OV() > SETV && diffcheck() && inputVok() && currentok()){
    digitalWrite(motor0Rev, HIGH);
  } else {
    digitalWrite(motor0Rev, LOW);
  }

  display("run",0);

}

int IV() {
  return analogRead(inVolt);
}

int OV() {
  return analogRead(outVolt);
}

int amp() {
  return analogRead(current);
}

void home() {
  display("SETP", 0);
}

void menuIHV() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("IHu", 0);
  }
}

void menuILV() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("ILu", 0);
  }
}

void menuOHV() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("OHu", 0);
  }
}

void menuOLV() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("OLu", 0);
  }
}

void menuSETV() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("SETu", 0);
  }
}

void menuOVL() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("OuL", 0);
  }
}

void menuTON() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("tOn", 0);
  }
}

void menuTOFF() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("tOFF", 0);
  }
}

void menuDIFF() {
  if(refresh.triggered(false)){
    displayVar(enc, 0);
  } else {
    display("dIFF", 0);
  }
}

void runSetup() {
  if(encMenu == 0) {
    home();
  }
  if(encMenu == 1) {
    menuIHV();
  }
  if(encMenu == 2) {
    menuILV();
  }
  if(encMenu == 3) {
    menuOHV();
  }
  if(encMenu == 4) {
    menuOLV();
  }
  if(encMenu == 5) {
    menuSETV();
  }
  if(encMenu == 6) {
    menuOVL();
  }
  if(encMenu == 7) {
    menuTON();
  }
  if(encMenu == 8) {
    menuTOFF();
  }
  if(encMenu == 9) {
    menuDIFF();
  }
  if(encMenu > 9) {
    encMenu = 0;
  }
  if(encMenu < 0) {
    encMenu = 9;
  }
}



void checkok() {
  if(read(ok) && okold == !read(ok)){
  okold = read(ok);
  encMenu++;
  refresh.reset();
  encUpdate();
  eepromUpdate();
  }
  if(read(ok) == false){
  okold = read(ok);
  }
}

void eepromUpdate() {
  EEPROM.update(0, IHV/2);
  EEPROM.update(1, ILV/2);
  EEPROM.update(2, OHV/2);
  EEPROM.update(3, OLV/2);
  EEPROM.update(4, SETV/2);
  EEPROM.update(5, OVL);
  EEPROM.update(6, TON);
  EEPROM.update(7, TOFF);
  EEPROM.update(8, DIFF);
}

void encUpdate() {
  if(encMenu == 0) {
    DIFF = enc;
  }
  if(encMenu == 1) {
    enc = IHV;
    }
  if(encMenu == 2) {
    IHV = enc;
    enc = ILV;
    }
  if(encMenu == 3) {
    ILV = enc;
    enc = OHV;
    }
  if(encMenu == 4) {
    OHV = enc;
    enc = OLV;
    }
  if(encMenu == 5) {
    OLV = enc;
    enc = SETV;
    }
  if(encMenu == 6) {
    SETV = enc;
    enc = OVL;
    }
  if(encMenu == 7) {
    OVL = enc;
    enc = TON;
    }
  if(encMenu == 8) {
    TON = enc;
    enc = TOFF;
    }
  if(encMenu == 9) {
    TOFF = enc;
    enc = DIFF;
    }
}

void displayVar(int var, int deci) {
  char buffer[5];
  sprintf(buffer, "%04d", var);
  display1.DisplayString(buffer, deci);
}

void checkplus() {
  if(read(plus) && plusold == !read(plus)){
  plusold = read(plus);
  enc++;
  }
  if(read(plus) == false){
  plusold = read(plus);
  }
}

void checkminus() {
  if(read(minus) && minusold == !read(minus)){
  minusold = read(minus);
  enc--;
  }
  if(read(minus) == false){
  minusold = read(minus);
  }
}

void setIN(int PIN) {
  pinMode(PIN, INPUT);
}

void setOUT(int PIN) {
  pinMode(PIN, OUTPUT);
}

bool read(int PIN) {
  if(digitalRead(PIN)) {
    return true;
  } else {
    return false;
  }
}

void display(String str, int deci) {
  int strl = str.length();
  if(strl < 4) {
    str = char(16) + str;
  }

  int str_len = str.length() + 1;
  char data[str_len];
  str.toCharArray(data, str_len);
  display1.DisplayString(data, deci);
}

void setupDisplay() {
    int displayType = COMMON_CATHODE;

   int digit1 = 2; 
   int digit2 = 3; 
   int digit3 = 4; 
   int digit4 = 5; 
   
   
   int segA = 6; 
   int segB = 7;
   int segC = 8; 
   int segD = 9; 
   int segE = 10; 
   int segF = 11; 
   int segG = 12; 
   int segDP = 13; 
   
  int numberOfDigits = 4; 

  display1.Begin(displayType, numberOfDigits, digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, segDP);
  
  display1.SetBrightness(100); 
  // put your setup code here, to run once:
  
}

#include <EEPROM.h>
#include <BlockNot.h>
#include "SevSeg.h"


SevSeg display1;

//BlockNot screen(2, SECONDS);
BlockNot INHV(200);
bool setupm = false;
int IHV;
int enc;
const int ok = 2;
const int plus = A1;
const int minus = A2;
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
IHV = EEPROM.read(0);
//attachInterrupt(A3, encmenuup, RISING);
}

void loop() {
  checkok();
  checkplus();
  checkminus();

  if(encMenu == 0) {
    display("Abc1", 0);
  }
  if(encMenu == 1) {
    display("EF02", 0);
  }
  if(encMenu == 2) {
    display("Ab03", 0);
  }
  if(encMenu == 3) {
    display("0003", 0);
  }
  if(encMenu == 4) {
    display("0004", 0);
  }
  if(encMenu == 5) {
    display("0005", 0);
  }
  if(encMenu == 6) {
    display("0006", 0);
  }
  if(encMenu == 7) {
    display("0007", 0);
  }
  if(encMenu == 8) {
    display("0008", 0);
  }
  if(encMenu > 8) {
    encMenu = 0;
  }
  if(encMenu < 0) {
    encMenu = 8;
  }



  
}


void checkok() {
  if(read(ok) && okold == !read(ok)){
  okold = read(ok);
  encMenu++;
  }
  if(read(ok) == false){
  okold = read(ok);
  }
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
  enc++;
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
  if(digitalRead(PIN) == true) {
    return false;
  } else {
    return true;
  }
}

void display(String str, int deci) {
  int str_len = str.length() + 1;
  char data[str_len];
  str.toCharArray(data, str_len);
  display1.DisplayString(data, deci);
}

void setupDisplay() {
    int displayType = COMMON_CATHODE;

   int digit1 = A0; 
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

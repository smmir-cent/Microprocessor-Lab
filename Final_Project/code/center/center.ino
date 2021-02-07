#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>
#define ADDRESS 0b1010000
#define validIn 4
#define wrongIn 5
#define timerErr 3

//keypad
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', 'E', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {23, 25, 27, 29}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//lcd
const int rs = 13 , en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//logic
int Temp = 0 ;
char illegal[100][4] ;
char Pass[4] ;
bool valid = false ;
bool IsOpen = false ;
unsigned long startTime = 0;

int timer = 10;
int a = 0, b = 0, c = 0, d = 0;
int len = 0;

void setup() {
  lcd.begin(16, 2);
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Temp = 0;
  pinMode(timerErr, OUTPUT);
  pinMode(validIn, OUTPUT);
  pinMode(wrongIn, OUTPUT);
  digitalWrite(validIn, LOW);
  digitalWrite(wrongIn, LOW);
  //********loading from eeprom
  loading();
}
int mili0;
int sec0;
int min0;
void loop() {
  if (IsOpen && ((millis() - startTime) / 100 > timer)) {
    digitalWrite(timerErr, HIGH);
    closing();
  }
  if (Serial.available() > 0) {
    char can = char(Serial.read());
    if ( IsOpen && can == 'A') {
      a++;
      closing();
      updating();
    }
  }
  if (Serial1.available() > 0) {
    char can = char(Serial1.read());
    if (IsOpen && can == 'B') {
      b++;
      closing();
      updating();
    }
  }
  if (Serial2.available() > 0) {
    char can = char(Serial2.read());
    if (IsOpen && can == 'C') {
      c++;
      closing();
      updating();
    }
  }
  if (Serial3.available() > 0) {
    char can = char(Serial3.read());
    if (IsOpen && can == 'D') {
      d++;
      closing();
      updating();
    }
  }
  char customKey = customKeypad.getKey();
  if (customKey) {
    //get number
    if (customKey != '*' && customKey != 'C' && customKey != 'E' && customKey != '/' && customKey != '-' && customKey != '+') {
      if (Temp < 4)
        Pass[Temp] = customKey;
      Temp++;
    }
    //to open
    else if (customKey == '*') {
      valid = validation();
      Temp = 0 ;
      //delay(100);
      digitalWrite(timerErr, LOW);
      if (!valid) {
        digitalWrite(wrongIn, HIGH);
      }
      else {
        //******send open state and add it to illegal
        Serial.write('?');
        Serial1.write('?');
        Serial2.write('?');
        Serial3.write('?');
        digitalWrite(validIn, HIGH);
        digitalWrite(wrongIn, LOW);
        startTime = millis();
        IsOpen = true ;
      }
    }
    else if (customKey == 'C') {
      digitalWrite(timerErr, LOW);
      digitalWrite(validIn, LOW);
      digitalWrite(wrongIn, LOW);
      Temp = 0;
      valid = false;
    }
    //to close
    else if (customKey == '/') {
      closing();
    }
    //change timer
    else if (customKey == '+') {
      timer = converting();
    }
  }
}
void closing() {
  if (IsOpen) {
    //*********send not open state
    Serial.write('x');
    Serial1.write('x');
    Serial2.write('x');
    Serial3.write('x');
    strcpy(illegal[len], Pass);
    len++;
    digitalWrite(validIn, LOW);
    digitalWrite(wrongIn, LOW);
    IsOpen = false ;
    Temp = 0;
  }
}

int converting() {
  int num = 0;
  for (int i = Temp; i < 4 ; i++ ) {
    Pass[i] = 0;
  }
  num = atoi(Pass);
  for (int i = 0 ; i < 10 ; i++ ) {
    Pass[i] = 0;
  }
  Temp = 0 ;
  return num;
}
bool validation() {
  if (Temp == 4) {
    for (int i = 0; i < len; i++) {
      for (int j = 0 ; j < 4 ; j++) {
        if (illegal[i][j] != Pass[j]) {
          break ;
        }
        if (j == 3) {
          return false;
        }
      }
    }
    return true;
  }
  digitalWrite(A1, HIGH);
  return false;
}

void updating() {
  //lcd
  show();
  //e2prom
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);
  Wire.write(0xAA);
  Wire.write(a);
  Wire.write(b);
  Wire.write(c);
  Wire.write(d);
  Wire.endTransmission();
  delay(1000);
}
void loading() {
  //lcd
  //e2prom
  uint8_t val;
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);
  Wire.write(0xAA);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 4);
  val = Wire.read();
  a = val ;
  val = Wire.read();
  b = val ;
  val = Wire.read();
  c = val ;
  val = Wire.read();
  d = val ;
//delay(1000);

  show();
}
void show() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A:");
  lcd.print(a);
  lcd.setCursor(8, 0);
  lcd.print("B:");
  lcd.print(b);
  lcd.setCursor(0, 1);
  lcd.print("C:");
  lcd.print(c);
  lcd.setCursor(8, 1);
  lcd.print("D:");
  lcd.print(d);
}
//
//#include <LiquidCrystal.h>
//#include <Keypad.h>
//#include <Wire.h>
//#define ADDRESS 0b1010000
//#define validIn 4
//#define wrongIn 5
//#define timerErr 3
//
//void setup(){
//  Wire.beginTransmission(ADDRESS);
//  Wire.write(0x00);
//  Wire.write(0xAA);
//  Wire.write(0);
//  Wire.write(0);
//  Wire.write(0);
//  Wire.write(0);
//  Wire.endTransmission();
//  delay(1000);
//  pinMode(timerErr, OUTPUT);
//
//}
//void loop(){
//  digitalWrite(timerErr, HIGH);
//}

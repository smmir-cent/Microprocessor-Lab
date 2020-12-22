#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>
#define serv 6
#define buz 7
#define ledO 4
#define ledC 5

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


Servo servo;

//logic
int Temp;
char Origin_Pass[] = {'1', '2', '3', '4'};
char Pass[4] ;
bool Wrong_Pass = false ;
bool IsOpen = false ;
unsigned long startTime = 0;
unsigned long veri = 0;
bool verified = false ;
int timer = 5;
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  Temp = 0;
  servo.attach(6);
  pinMode(serv, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(ledO, OUTPUT);
  pinMode(ledC, OUTPUT);
  //len = 0;
  servo.write(0);
  digitalWrite(ledO, LOW);
  digitalWrite(ledC, HIGH);
}
int mili0;
int sec0;
int min0;
void loop() {
  if (IsOpen) {
    sec0 = timer % 60 - ((millis() / 1000) % 60) + (startTime / 1000) % 60;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Open");
    lcd.setCursor(0, 1);
    lcd.print("Closing time:");
    lcd.print(sec0);
    delay(100);
  }
  if (IsOpen && millis() - startTime > timer * 1000) {
    closing();
  }
  char customKey = customKeypad.getKey();
  if (customKey) {
    //get number
    if (customKey != '*' && customKey != 'C' && customKey != 'E' && customKey != '/' && customKey != '-' && customKey != '+') {
      //lcd.print(customKey);
      if (Temp < 4)
        Pass[Temp] = customKey;
      Temp++;
    }
    //to open
    else if (customKey == '*') {
      if (Temp == 4) {
        for (int i = 0 ; i < 4 ; i++) {
          if (Origin_Pass[i] != Pass[i]) {
            Wrong_Pass = true ;
            break ;
          }
        }
      }
      else {
        Wrong_Pass = true ;
      }
      lcd.clear();
      lcd.setCursor(0, 1);
      if (Wrong_Pass) {
        lcd.print(" Wrong password ");
        Temp = 0 ;
        Wrong_Pass = false ;
        verified = false;


      }
      else {
        lcd.print("Correct password");
        digitalWrite(ledO, HIGH);
        digitalWrite(ledC, LOW);
        digitalWrite(buz, HIGH);
        for (int pos = 0; pos <= 180; pos += 1) {
          servo.write(pos);
          delay(15);
        }
        digitalWrite(buz, LOW);
        startTime = millis();
        IsOpen = true ;
        verified = true ;
      }
    }
    //to clear lcd
    else if (customKey == 'C') {
      lcd.clear();
      Temp = 0;
      Wrong_Pass = false;
    }
    //to change password
    else if (customKey == 'E') {
      if (!verified || ((millis() - veri) / 1000) > 60) {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(" please open it ");
        Temp == 0 ;
      }
      else if (verified && Temp == 4) {
        for (int i = 0 ; i < 4 ; i++) {
          Origin_Pass[i] = Pass[i];
        }
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("  New pass set  ");
        IsOpen = false ;
        verified = false ;
        Temp= 0 ;
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("PW must be 4 num");
        Temp == 0 ;
      }
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
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Closing...");
    digitalWrite(ledO, LOW);
    digitalWrite(ledC, HIGH);
    digitalWrite(buz, HIGH);
    for (int pos = 180; pos >= 0; pos--) {
      servo.write(pos);
      delay(15);
    }
    digitalWrite(buz, LOW);
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

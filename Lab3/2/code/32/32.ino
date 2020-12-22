#include <LiquidCrystal.h>
#include <Keypad.h>

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
int Temp;
char Origin_Pass[] = {'1', '2', '3', '4'};
char Pass[4] ;
bool Wrong_Pass = false ;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  Temp = 0;
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey) {
    if (customKey != '*' && customKey != 'C') {
      lcd.print(customKey);
      if (Temp < 4)
        Pass[Temp] = customKey;
      Temp++;
    }
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
      lcd.setCursor(0, 1);
      if (Wrong_Pass) {
        lcd.print(" Wrong password ");
      }
      else {
        lcd.print("Correct password");
      }
    }
    else if (customKey == 'C') {
      lcd.clear();
      Temp = 0;
      Wrong_Pass = false;
    }
  }
}

#include <LiquidCrystal.h>
#include <Keypad.h>

//keypad
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = {31, 33, 35, 37};
byte colPins[COLS] = {23, 25, 27, 29};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//lcd
const int rs = 13 , en = 12, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//logic
char Operator = NULL;
int len ;
long int num1;
long int num2;
char nums[10] ;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  len = 0;
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey) {
    lcd.print(customKey);
    if (customKey == '+') {
      Operator = '+';
      num1 = converting(nums);
      len = 0;
    }
    else if (customKey == '-') {
      Operator = '-';
      num1 = converting(nums);
      len = 0;
    }
    else if (customKey == '/') {
      Operator = '/';
      num1 = converting(nums);
      len = 0;
    }
    else if (customKey == '*') {
      Operator = '*';
      num1 = converting(nums);
      len = 0;
    }
    else if (customKey == 'C') {
      lcd.setCursor(0, 0);
      lcd.clear();
      len = 0;
      Operator = NULL;
      num1 = 0;
      num2 = 0;
    }
    else if (customKey == '=') {
      num2 = converting(nums);
      lcd.setCursor(0, 1);
      len = 0;
      switch (Operator) {
        case '+':
          lcd.print(num1 + num2);
          break;
        case '-':
          lcd.print(num1 - num2);
          break;
        case '*':
          lcd.print(num1 * num2);
          break;
        case '/':
          lcd.print(num1 / num2);
          break;
      }
    }
    else {
      nums[len] = customKey ;
      len++;
    }
  }
}
int converting(char* nums) {
  long int num = 0;
  for (int i = len; i < 10 ; i++ ) {
    nums[i] = 0;
  }
  num=atoi(nums);
  for (int i = 0 ; i < 10 ; i++ ) {
    nums[i] = 0;
  }
  return num;
}

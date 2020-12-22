#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h>

#define led1 4
#define led2 5
#define led3 6
#define led4 7
#define ADDRESS 0b1010000


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

int mili0;
int sec0;
int min0;

char temp[4];
int len = 0 ;
int timer[4] = {5, 5, 5, 5} ;
int mode = 0;
int index = 0 ;
int modes[7][4] = {{1, 2, 3, 4}, {1, 2, 4, 0}, {1, 3, 4, 0}, {2, 3, 4, 0}, {1, 4, 0, 0}, {2, 4, 0, 0}, {3, 4, 0, 0}};
int time0 = 0 ;
int step0 = 0;
void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  while (true) {
    char customKey = customKeypad.getKey();
    if (customKey) {
      //get number
      if (customKey != '*' && customKey != 'C' && customKey != 'E' && customKey != '/' && customKey != '-' && customKey != '+') {
        //lcd.print(customKey);
        if (len < 4)
          temp[len] = customKey;
        len++;
      }
      //to execute
      else if (customKey == '*') {
        mode = converting();
        if (mode < 8 && mode > 0) {
          mode--;
        }
        else {
          mode = 0;
        }
        index = 0;
        char key;
        unsigned long t = millis();
        time0 = 0;
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
        while (true) {
          int temp0 = modes[mode][index];
          if (millis() - t > 1000) {
            time0++;
            t = millis();
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("time: ");

            lcd.print(timer[temp0 - 1] - time0);
          }




          if (timer[temp0 - 1] == time0) {
            digitalWrite(led1, LOW);
            digitalWrite(led2, LOW);
            digitalWrite(led3, LOW);
            digitalWrite(led4, LOW);
            Serial.println(modes[mode][index]);
            index++;
            time0 = 0;
            t = millis();
          }
          if (index >= 4 || modes[mode][index] == 0) {
            finish();
            break;
          }

          key = customKeypad.getKey();
          if (key == '/') {
            key = customKeypad.waitForKey();
          }

          if (modes[mode][index] == 1) {
            digitalWrite(led1, HIGH);
          }
          else if (modes[mode][index] == 2) {
            digitalWrite(led2, HIGH);
          }
          else if (modes[mode][index] == 3) {
            digitalWrite(led3, HIGH);
          }
          else if (modes[mode][index] == 4) {
            digitalWrite(led4, HIGH);
          }
        }
      }
      else if (customKey == 'C') {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("defaultmode:1234");
        len = 0 ;
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        digitalWrite(led4, LOW);
      }
      //change timer
      else if (customKey == '+') {
        int s = converting();
        if (step0 != 0) {
          timer[step0 - 1] = s;
          writing();
          loading();
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("defaultmode:1234");
          lcd.setCursor(0, 1);
          lcd.print("Timer");
          lcd.print(step0);
          lcd.print(" changed");
          step0 = 0;

        }
        else if (s != 1 && s != 2 && s != 3 && s != 4) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("defaultmode:1234");
          lcd.setCursor(0, 1);
          lcd.print("  Invalid step  ");
        }
        else {
          step0 = s;
        }
      }
    }

  }
}
void loading() {
  uint8_t val;
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);
  Wire.write(0xAA);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 32);
  for (int i = 0; i < 4 ; i++) {
    val = Wire.read();
    timer[i] = val ;
  }
  for (int i = 0; i < 7 ; i++) {
    for (int j = 0; j < 4 ; j++) {
      val = Wire.read();
      modes[i][j] = val ;
    }
  }

}
void writing() {
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);
  Wire.write(0xAA);
  for (int i = 0; i < 4 ; i++) {
    Wire.write(timer[i]);
  }
  for (int i = 0; i < 7 ; i++) {
    for (int j = 0; j < 4 ; j++) {
      Wire.write(modes[i][j]);
    }
  }
  Wire.endTransmission();
  delay(1000);
}



int converting() {
  int num = 0;
  for (int i = len; i < 4 ; i++ ) {
    temp[i] = 0;
  }
  num = atoi(temp);
  for (int i = 0 ; i < 10 ; i++ ) {
    temp[i] = 0;
  }
  len = 0 ;
  return num;
}


void finish() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  time0 = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("defaultmode:1234");
  lcd.setCursor(0, 1);
  lcd.print("   finished   ");
}

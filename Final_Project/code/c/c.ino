#include <Keypad.h>
#define openLed 7
#define blockLed 6
#define wrongLed 5
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

boolean isOpen = false;
char command = NULL;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(openLed, OUTPUT);
  pinMode(blockLed, OUTPUT);
  pinMode(wrongLed, OUTPUT);

}
void loop() {
  // put your main code here, to run repeatedly:
  char customKey;
  if (Serial.available() > 0) {
    command = char(Serial.read());
    if (command == '?') {
      isOpen = true;
      digitalWrite(openLed, LOW);
      digitalWrite(blockLed, LOW);
      digitalWrite(wrongLed, LOW);
    }
    else if (command == 'x') {
      isOpen = false;
      digitalWrite(blockLed, HIGH);
      digitalWrite(wrongLed, LOW);

    }
  }
  if (isOpen) {
    customKey = customKeypad.getKey();
    if (customKey) {
      if(customKey == '0'){
        Serial.write('C');
        digitalWrite(openLed, HIGH);
        digitalWrite(wrongLed, LOW);
      }
      else{
        digitalWrite(wrongLed, HIGH);
      }
    }
  }
}

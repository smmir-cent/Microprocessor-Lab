#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};
byte rowPins[ROWS] = {23, 25, 27, 29};
byte colPins[COLS] = {31, 33, 35, 37};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Servo myservo;
int pos = 0;
void setup() {
  Serial3.begin(9600);
  myservo.attach(13);
}
String snum ;
int num ;
void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '=') {
      if (isValid(snum.toInt()))
        myservo.write(snum.toInt());
      delay(20);
      snum = "";
    } else if (key == 'C') {
      snum = "";
    } else {
      snum += key;
    }
  }
}
bool isValid(int num) {
  if (num <= 180 && num >= 0) {
    Serial3.print(num);
    Serial3.println(" :Valid data");
    return true ;
  }
  else {
    Serial3.print(num);
    Serial3.println(" :Invalid data");
    return false ;
  }
}

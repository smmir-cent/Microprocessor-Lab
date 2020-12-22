
#include <Servo.h>

Servo myservo;

void setup() {
  Serial3.begin(9600);
  myservo.attach(13);
  myservo.write(0);
}
String snum = "" ;
int value ;
void loop() {
  if (Serial3.available() > 0) {

    int key = Serial3.read() - 48;
    if (key == 13) {
      value = snum.toInt();
      if (isValid(value)) {
        if ( myservo.read() + value <= 180  ) {
          myservo.write(myservo.read() + value);
        }else if(myservo.read() - value >= 0){
          myservo.write(myservo.read() - value);
        }else {
          Serial3.println("Can't move");
        }
      }
      snum = "";
      delay(20);
    } else if (key == -2) {
      snum = "";
      Serial3.println("Clear");
    } else {
      snum += key;
    }
  }
}
bool isValid(int num) {
  if (num <= 180 && num >= 0) {
    Serial3.println("Valid data");
    return true ;
  }
  else {
    Serial3.println("Invalid data");
    return false ;
  }
}

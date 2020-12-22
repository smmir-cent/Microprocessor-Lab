
#include <Servo.h>
Servo myservo;
int val ;
void setup() {
  Serial3.begin(9600);
  myservo.attach(13);
}
void loop() {
  val = analogRead(A0);
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);
  delay(10);
}

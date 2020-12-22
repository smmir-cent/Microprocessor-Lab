
#include <Servo.h>

#define serv 9
#define buz 10
#define arm 11
#define led 12

Servo servo;
char num[10] ;
int len ;
void setup() {
  Serial3.begin(9600);
  servo.attach(serv);
  pinMode(serv, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(arm, OUTPUT);
  pinMode(led, OUTPUT);
  len = 0;
  servo.write(90);
}
byte inbyte = 0;
void loop() {
  if (Serial3.available() > 0) {
    inbyte = Serial3.read();
    int entered = inbyte ;
    if (entered == '.') {
      int number = converting();
      Serial3.println();
      if ( number == 0) {
        Serial3.println("0:help");
        Serial3.println("11:buzzer on");
        Serial3.println("12:buzzer off");
        Serial3.println("21:led on");
        Serial3.println("22:led off");
        Serial3.println("31:motor on");
        Serial3.println("32:motor off");
        Serial3.println("41:led angle: 60");
        Serial3.println("42:led angle: 90");
        Serial3.println("43:led angle: 135");
      }
      //buzz on
      else if (number == 11) {
       digitalWrite(buz, HIGH);
      }
      //buz off
      else if (number == 12) {
        digitalWrite(buz, LOW);
      }
      //led on
      else if (number == 21) {
        digitalWrite(led, HIGH);
      }
      //led off
      else if (number == 22) {
        digitalWrite(led, LOW);
      }
      //arm on
      else if (number == 31) {
        digitalWrite(arm, HIGH);
      }
      //arm off
      else if (number == 32) {
        digitalWrite(arm, LOW);
      }
      //serv on 45
      else if (number == 41) {
        servo.write(60);
      }
      //serv on 90
      else if (number== 42) {
        servo.write(90);
      }
      //serv on 135
      else if (number== 43) {
        servo.write(135);
      }
      else{
        Serial3.println("Wrong Input");
      }
    }
    else{
      num[len++] = char(entered) ;
    }
  }
}
int converting() {
  int number = 0;
  char temp[len];
  for (int i = 0; i < len ; i++ ) {
     temp[i]=num[i] ; 
  }
  len = 0;
  number=atoi(temp);
  for (int i = 0 ; i < 10 ; i++ ) {
    num[i] = '0';
  }
  return number;
}

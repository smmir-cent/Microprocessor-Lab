/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>
#define led1 A0
#define led2 A1
#define led3 A2
#define led4 A3
#define led5 A7
#define led6 A6
#define led7 A5
#define led8 A4
#define led9 A8
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'7','8','9','A'},
  {'4','5','6','B'},
  {'1','2','3','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {23, 25, 27, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 33, 35, 37}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial3.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  pinMode(led7,OUTPUT);
  pinMode(led8,OUTPUT); 
  pinMode(led9,OUTPUT);
}
void loop(){
  char customKey = customKeypad.getKey(); 
  if(customKey){
    Serial3.println(customKey);
    if (customKey == '1'){
      digitalWrite(led1,HIGH);
    }
    else if(customKey == '2'){
      digitalWrite(led2,HIGH);
    }
    else if(customKey == '3'){
      digitalWrite(led3,HIGH);
    }
    else if(customKey == '4'){
      digitalWrite(led4,HIGH);
    }
    else if(customKey == '5'){
      digitalWrite(led5,HIGH);
    }
    else if(customKey == '6'){
      digitalWrite(led6,HIGH);
    }
    else if(customKey == '7'){
      digitalWrite(led7,HIGH);
    }
    else if(customKey == '8'){
      digitalWrite(led8,HIGH);
    }
    else if(customKey == '9'){
      digitalWrite(led9,HIGH);
    }
    else if(customKey == '0'){
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
    }
  }
}

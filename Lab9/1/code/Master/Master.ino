#include <SPI.h>
const int SS1 = 45, SS2 = 46;
void setup(){
  Serial3.begin(9600);
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop(){
    digitalWrite(SS1, LOW);
    byte s1[] = {'S', 'l', 'a', 'v', 'e' ,'1'};
    delay(10);
    for(int i = 0 ; i < 6 ; i++){
      SPI.transfer(s1[i]);
    }
    delay(10);
    digitalWrite(SS1, HIGH);
    delay(500);


    
    digitalWrite(SS2, LOW);
    delay(10);
    byte s2[] = {'S', 'l', 'a', 'v', 'e' ,'2'};
    for(int i = 0 ; i < 6 ; i++){
      SPI.transfer(s2[i]);
    }
    delay(10);
    digitalWrite(SS2, HIGH);  
    delay(500);
  
}

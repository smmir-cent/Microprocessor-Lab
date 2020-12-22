#include <SPI.h>

#define input 51

byte buf[6];
byte index = 0;
boolean IsFinished = false;


void setup() {
  Serial3.begin (9600);
  pinMode(input, INPUT_PULLUP);
  SPCR |= _BV(SPE);
  SPCR |= _BV(SPIE);
  SPI.attachInterrupt();
}
void loop() {
  if (IsFinished) {
    IsFinished = false;
    for (int i = 0 ; i < 6 ; i++) {
      char c = buf[i];
      Serial3.print(c);
    }
    Serial3.println("");
    index = 0;
  }
}
ISR(SPI_STC_vect) {
  byte b = SPDR;

  buf[index] = b;
  index++;
  if (index == 6)
    IsFinished = true;

}

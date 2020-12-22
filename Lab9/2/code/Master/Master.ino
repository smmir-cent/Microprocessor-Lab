#include <SPI.h>

#define Sensor A1
#define Resistor A0

const int SS1 = 45, SS2 = 46;
byte resistorBytes[2], sensorBytes[2];
int sensorInput, resistorInput;

byte rb , sb ;
void setup() {
  Serial3.begin(9600);
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
  digitalWrite(SS1, HIGH);
  digitalWrite(SS2, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop() {
  resistorInput = analogRead(Resistor);
  sensorInput = analogRead(Sensor);

  int TempCel = ( sensorInput * 500)/1023;
  Serial3.print("Sensor = ");
  Serial3.println(TempCel);
  Serial3.print("Resistor = ");
  Serial3.println(resistorInput);
  resistorBytes[0] = resistorInput;
  resistorBytes[1] = resistorInput >> 8;
  sensorBytes[0] = TempCel;
  sensorBytes[1] = TempCel >> 8;
  
  digitalWrite(SS1, LOW);
  delay(10);
  for (int i = 0 ; i < 2 ; i++) {
    SPI.transfer(resistorBytes[i]);
  }
  delay(10);
  digitalWrite(SS1, HIGH);
  delay(500);

  digitalWrite(SS2, LOW);
  delay(10);
  for (int i = 0 ; i < 2 ; i++) {
    SPI.transfer(sensorBytes[i]);
  }
  delay(10);
  digitalWrite(SS2, HIGH);
  delay(200);
}

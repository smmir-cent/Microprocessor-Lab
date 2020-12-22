const int buttonPin1 = 10;
const int buttonPin2 = 11;
const int buttonPin3 = 12;
const int ledPin0 =  0;
const int ledPin1 =  1;
const int ledPin2 =  2;
const int ledPin3 =  3;
const int ledPin4 =  4;
const int ledPin5 =  5;
const int ledPin6 =  6;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  if (buttonState1 == LOW && buttonState2 == HIGH && buttonState3 == HIGH) {
    digitalWrite(ledPin0, HIGH);
    delay (1000);
    digitalWrite(ledPin1, HIGH);
    delay (1000);
    digitalWrite(ledPin2, HIGH);
    delay (1000);
    digitalWrite(ledPin3, HIGH);
    delay (1000);
    digitalWrite(ledPin4, HIGH);
    delay (1000);
    digitalWrite(ledPin5, HIGH);
    delay (1000);
    digitalWrite(ledPin6, HIGH);
  } else if(buttonState1 == HIGH && buttonState2 == LOW && buttonState3 == HIGH) {
    digitalWrite(ledPin6, HIGH);
    delay (1000);
    digitalWrite(ledPin5, HIGH);
    delay (1000);
    digitalWrite(ledPin4, HIGH);
    delay (1000);
    digitalWrite(ledPin3, HIGH);
    delay (1000);
    digitalWrite(ledPin2, HIGH);
    delay (1000);
    digitalWrite(ledPin1, HIGH);
    delay (1000);
    digitalWrite(ledPin0, HIGH);
  }
  else if(buttonState1 == HIGH && buttonState2 == HIGH && buttonState3 == LOW) {
    digitalWrite(ledPin6, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin0, LOW);
  }
  
}

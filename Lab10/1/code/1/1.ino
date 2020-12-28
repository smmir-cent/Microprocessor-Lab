#include "pitches.h"
#include "ey_iran.h"
//#include "Jingle.h"
//#include "Ode.h"
//#include "themes.h"
//#include "themes2.h"
//#include "themes1.h"


int val = 0;
float scale = 0;
int inPin = 7;
int thisNote = 0;
void setup() {
  pinMode(7, INPUT);

}

void loop() {
  val = digitalRead(inPin);

  if (val == 0) {
    for (; thisNote < sizeof(melody) / sizeof(int); thisNote++) {
      scale = analogRead(A0) / 512.0;
      int noteDuration = 500 / noteDurations[thisNote];
      tone(8, (int)melody[thisNote]*scale, noteDuration);
      delay((int)noteDuration * 1.3);
      val = digitalRead(inPin);
      if (val != 0) {
        break;
      }
    }
    if(thisNote == sizeof(melody) / sizeof(int)){
      thisNote = 0;
    }
  }

}

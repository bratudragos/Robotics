#include "pitches.h"

int melody[] = {
NOTE_F3, NOTE_CS3, NOTE_B2, NOTE_DS3, NOTE_FS3, NOTE_GS3,
NOTE_F3, NOTE_CS3, NOTE_B2, NOTE_DS3
};
int noteDurations[] = {
2, 4, 2, 4, 4, 4, 2, 4, 2, 4
};
const int passivePin = A2;
int passiveValue=0;
const int activePin=11;
int toneToProduce=600;
const int buttonPin=2;
int buttonValue=0;
const int threshold = 1;
int lastTimePlayed=0;
int timeDifference=0;
int timePressed=0;
int timeCount=0;

void setup() {
pinMode(passivePin, INPUT);
pinMode(activePin,OUTPUT);
pinMode(buttonPin,INPUT);
Serial.begin(9600);
}

void loop() {
passiveValue = analogRead(passivePin);
timeCount=millis();

if(passiveValue>=10){
  timePressed=millis();
  while(timeCount-timePressed<5000){
    timeCount=millis();
  }
  passiveValue=0;
  for (int thisNote = 0; thisNote < 10; thisNote++) {
    buttonValue=digitalRead(buttonPin);
    if(buttonValue==1){
      break;
    }
    int noteDuration = 2000 / noteDurations[thisNote];
    tone(activePin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.06;
    delay(pauseBetweenNotes);
    }
  }
}

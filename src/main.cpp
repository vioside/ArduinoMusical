#include "Arduino.h"
int beats_per_second = 1;
int noOfPins = 8;
int pins[] = { 30, 26, 24, 36, 38, 40, 42, 44 };

//1 = whole note, 2 = half note, 4 = quarter note, 8 = eigth note, 16 = sixteenth note
int noOfNotes = 25;
int notes[] = { 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 1, 4, 4, 2, 8, 4, 4, 2, 8, 4, 4, 4, 4, 2, 1 };

void switchPin(int number, int duration, bool on) {
    if(on) {
        digitalWrite(pins[number], HIGH);
    }
    delay(duration);
    digitalWrite(pins[number], LOW);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0; i<noOfPins; i++) {
      pinMode(pins[i], OUTPUT);
  }
}

void loop() {
    delay(10000);
    int skip = 0;
    int number_buffer = 36; //can to be used to start from a higher pin
    for(int i=0; i<noOfNotes; i++) {
        int note = notes[i];
        int pin = pins[i];
        int number = i+number_buffer+skip;
        if(number == 46 || number == 56) { //can be used to skip number in case of a troblematic pin
            skip += 1;
            number += 1;
        }
        int duration = (beats_per_second*1000)/note; 
        switchPin(number, duration, true);

        if(i>=noOfNotes) {
            i=0;
            skip = 0;
        }
    }
}


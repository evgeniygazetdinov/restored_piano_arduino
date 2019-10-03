/* 
keyboard_midi001 - sketch to test basic keyboard matrix using teensy
and output midi across usb
By mit-mit
*/

#include "pitches.h"

// Stuff for running keyboard
char keystate[49] = {0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0};

char keystate_prev[49] = {0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0,0,0,0,0,0,
  0};

char pins_rows[6] = {10,9,8,7,6,5};
char pins_cols[9] = {1,2,3,4,11,12,13,14,15};

void init_keys() {
  for (int i = 0; i < 6; i++) {
    pinMode(pins_rows[i], OUTPUT);
    digitalWrite(pins_rows[i], LOW);
  }
  for (int i = 0; i < 9; i++) {
    pinMode(pins_cols[i], OUTPUT);
    digitalWrite(pins_cols[i], HIGH);
    
  }
}

// read_keys - Implements switch matrix
void read_keys() {
  int k = 0;
  Serial.print("ready for print");
  // Read bottom C
  digitalWrite(pins_cols[0], LOW);
  pinMode(pins_rows[5], INPUT_PULLUP);
  delayMicroseconds(10);
  if (digitalRead(pins_rows[5])) {
    keystate[k] = 0;
  }
  else {
    keystate[k] = 1;
  }
  pinMode(pins_rows[5], OUTPUT);
  digitalWrite(pins_rows[5], LOW);
  k++;
  digitalWrite(pins_cols[0], HIGH);
  
  // Read remaining keys
  for (int i = 1; i < 9; i++) {
    digitalWrite(pins_cols[i], LOW);
    for (int j = 0; j < 6; j++) {
      pinMode(pins_rows[j], INPUT_PULLUP);
      delayMicroseconds(10);
      if (digitalRead(pins_rows[j])) {
        keystate[k] = 0;
      }
      else {
        keystate[k] = 1;
      }
      pinMode(pins_rows[j], OUTPUT);
      digitalWrite(pins_rows[j], LOW);
      k++;
      delayMicroseconds(500);
    }
    digitalWrite(pins_cols[i], HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  
  // setup pin 13 LED for when keys pressed
  pinMode(13, OUTPUT);

  // Initialise all pins ready for cycling through reading
  init_keys();

}

void loop() {
  
  // read keys
  read_keys();
  
  // Output midi messages
  Serial.print(
  int played_note = 0;
  for (int i = 0; i < 49; i++) {
    if (keystate[i] == 1) {
      digitalWrite(13, HIGH);
      played_note = 1;
      if (keystate_prev[i] == 0) { // note on
        Serial.print("note on"); // 60 = C4
      }
    }
    else if (keystate_prev[i] == 1) { // note off
    Serial.print("note off");
    }
  }

  // Update previous states
  for (int i = 0; i < 49; i++) {
    keystate_prev[i] = keystate[i];
  }

  if (played_note == 0) { // light up keyboard
    digitalWrite(13, LOW);
  }

}

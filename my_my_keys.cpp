#include <stdio.h> // for function sprintf
char message[100];
char pins_rows[9] = {2,3,4,5,6,7,8,9,10};
//контакты тут
//add ground contacts
char ground_colums[6] = {11,12,13,A0,A1,A2};



void init_rows(){
    for(int i = 0; i <9; i++){
        pinMode(pins_rows[i],INPUT_PULLUP);
        digitalWrite(pins_rows[i],HIGH);
    }
    Serial.print("row inited");
}
void init_columns(){
    for(int i = 0; i <6; i++){
        pinMode(ground_colums[i],OUTPUT);
        digitalWrite(ground_colums[i],LOW);
    }
    Serial.print("column inited");
}



//TODO check this for on errors

void it_pressed_key(){
    //ошибка была в малом количестве)
    //
    for(int i = 0; i <9; i++){
    for(int y = 0;y< 6;y++){
    if (digitalRead(pins_rows [i]) == LOW){
    sprintf(message,"row %d is pressed",i);
    Serial.print(message);
    Serial.print("\n");
    }
    elseif (digitalRead(ground_colums[y] == HIGH){
      sprintf(message,"column %d is pressed",y);
      Serial.print(message);
    }
}
}



void setup(){
Serial.begin(9600);
init_rows();
init_columns();

}
void loop(){
it_pressed_key();    
delay(500);
}

/*

// 2-dimensional array of column pin numbers:
//const int col[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array of pixels:
int pixels[8][8];

// cursor position:
int x = 5;
int y = 5;

void setup() {
  // initialize the I/O pins as outputs iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
    digitalWrite(col[thisPin], HIGH);
  }

  // initialize the pixel matrix:
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pixels[x][y] = HIGH;
    }
  }
}

void loop() {
  // read input:
  readSensors();

  // draw the screen:
  refreshScreen();
}

void readSensors() {
  // turn off the last position:
  pixels[x][y] = HIGH;
  // read the sensors for X and Y values:
  x = 7 - map(analogRead(A0), 0, 1023, 0, 7);
  y = map(analogRead(A1), 0, 1023, 0, 7);
  // set the new pixel position low so that the LED will turn on in the next
  // screen refresh:
  pixels[x][y] = LOW;

}

void refreshScreen() {
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}


*/

#include <arduino2.h>

byte input_pins[] = {
  2, 3, 4, 5, 6, 7
};
byte output_pins[] = {
  30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40
};
/*GPIO_pin_t input_pins2[]= {
  DP2, DP3, DP4, DP5, DP6, DP7, DP8, DP9
};
GPIO_pin_t output_pins2[]= {
  DP30, DP31, DP32, DP33, DP34, DP35, DP36, DP37, DP38, DP39, DP40, DP41, DP42, DP43, DP44, DP45, DP46
};*/
int keys[] = {
  48, 49, 50, 51, 52, 53, //KO0
  54, 55, 56, 57, 58, 59, //KO1
  60, 61, 62, 63, 64, 65, //KO2
  66, 67, 68, 69, 70, 71, //KO3
  72, 73, 74, 75, 76, 77, //KO4
  78, 79, 80, 81, 82, 83, //KO5
  84, 85, 86, 87, 88, 89, //KO6
  90, 91, 92, 93, 94, 95, //KO7
  96, 97, 98, 99, 100, 101, //KO8
  102, 103, 104, 105, 106, 107, //KO9
  108, 0, 0, 0, 0, 0, 0, 0, //KO10
};
boolean signals[sizeof(input_pins) * sizeof(output_pins)];
boolean signals_old[sizeof(input_pins) * sizeof(output_pins)];
byte k;

//////////////////////////////////////////////
void setup() {
  for (byte pin = 0; pin < sizeof(input_pins); pin++)  {
    pinMode(input_pins[pin],INPUT_PULLUP);
  }
  for (byte pin = 0; pin < sizeof(output_pins); pin++) {
    pinMode(output_pins[pin],OUTPUT);
    digitalWrite(output_pins[pin],LOW);
  }
  for (byte s=0;s<sizeof(signals);s++){
    signals[s]=0;
  }
  pinMode(13,OUTPUT);
  digitalWrite2(13,LOW);

  //Serial.begin(38400);
  Serial.begin(31250);
  //Serial.begin(115200);
  delay(2000);
  Serial.write(0x90);
}

//////////////////////////////////////////////
void sendMIDI(byte command,byte key,byte velocity/*,byte channel*/) {
  Serial.write(command);
  Serial.write(key);
  Serial.write(velocity);
}

void sendMIDI2(byte key,byte velocity){
  Serial.write(key);
  Serial.write(velocity);
}
//////////////////////////////////////////////

void loop() {
  for (byte j=0;j<sizeof(signals);j++){
    signals_old[j]=signals[j]; //set signals_old to the last value of signals
  }
  k=0;
  //read the pin states
  for (byte o=0;o<sizeof(output_pins);o++){ //for each output pin
    digitalWrite2(output_pins[o],HIGH); //write the output pin high
    for (byte i=0;i<sizeof(input_pins);i++){ //for each input pin   
      signals[k]=digitalRead2(input_pins[i]); //save the value for each input_pullup
  //    Serial.print(signals[k]);
      k++;
    }
    digitalWrite2(output_pins[o],LOW);
  }
  

  //delay(10000);
  //check if there is a change in state, and if there is, send the MIDI message
  for (byte j=0;j<sizeof(signals);j++){
    if(signals[j]!=signals_old[j]){
      if(signals[j]==1){
        /*Serial.println(signals[j]);
        Serial.println(signals_old[j]);
        Serial.print("ON");
        Serial.println(keys[j]);
        delay(100);**/
        //sendMIDI(0x90,keys[j],127);
        sendMIDI2(keys[j],127);
      }
      else{
        /*Serial.println(signals[j]);
        Serial.println(signals_old[j]);
        Serial.print("OFF");
        Serial.println(keys[j]);
        delay(100);*/
        //sendMIDI(0x80,keys[j],0);
        sendMIDI2(keys[j],0);
      }
    }
  }
}

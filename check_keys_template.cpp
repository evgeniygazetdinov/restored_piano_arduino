#include <stdio.h> // for function sprintf
char message[100];
char pins_rows[9] = {2,3,4,5,6,7,8,9,10};
//контакты тут
//add ground contacts
char ground_colums[6] = {11,12,13,A0,A1,A2};
String  Notes[12] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"
};
//todo ADD NOTES TO FREQ ARRAY 
//for undestand which are be pressed

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


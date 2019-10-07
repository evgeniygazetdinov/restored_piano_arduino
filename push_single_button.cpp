//rigth push button without resistors;

int button = 2;

void setup(){

pinMode(button,INPUT);
digitalWrite(button,HIGH);
Serial.begin(9600);
}
void loop(){
if (digitalRead(button) ==LOW){
Serial.println("button is pressed");
}
delay(500);
}


#include <Keypad.h>
uint32_t val = 0;
const byte ROWS = 8;
const byte COLS = 6;
char keys[ROWS][COLS] = {
  {48,56,64,72,80,88},
  {49,57,65,73,81,89},
  {50,58,66,74,82,90},
  {51,59,67,75,83,91},
  {52,60,68,76,84,92},
  {53,61,69,77,85,93},
  {54,62,70,78,86,94},
  {55,63,71,79,87,95},
};
byte rowPins[ROWS] = {2, 3, 4, 5, 6, 7, 8, 9};
byte colPins[COLS] = {10, 11, A0, A1, A2, A3};
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;

int octave = 0;
int lstval = 0;
void setup() {
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(12, OUTPUT);
    Serial.begin(115200);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {
  if (digitalRead(A4) == HIGH)
  {
    delay(300);
    if (octave >= 36)
    {
      octave = 0;
    }
      else
      {
    octave = octave + 12;
      }
      alloff();
  }
  if (digitalRead(A5) == HIGH)
  {
    delay(300);
    if (octave <= -36)
    {
      octave = 0;
    }
      else
      {
    octave = octave - 12;
      }
      alloff();
  }
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)
        {
            if ( kpd.key[i].stateChanged )
            {
                switch (kpd.key[i].kstate) {
                    case PRESSED:
                    kpress(kpd.key[i].kchar);
                break;
                    case HOLD:
                break;
                    case RELEASED:
                    kreleased(kpd.key[i].kchar);
                break;
                    case IDLE:
                    break;
                }
            }
        }
    }
}
void noteOn(int cmd, unsigned long pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void kpress(char knum) {
  digitalWrite(12, HIGH);
    noteOn(0x90, ((knum - 7) + octave), 0x7F);
}
void kreleased(char knum) {
    noteOn(0x90, ((knum - 7) + octave), 0x00);
    digitalWrite(12, LOW);
}
void alloff() {
  digitalWrite(12, HIGH);
  for (int i=0; i <= 131; i++){
    noteOn(0x90, i, 0x00);
  }
  digitalWrite(12, LOW);
}

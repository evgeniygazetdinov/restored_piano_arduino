// Midi standard at 48 is the map to the casio-39 

/*
 * 
 *   Send out a mask and with the keybpard matrix check if that mask produces a key pressed loop thru the set and good 2 go
 * 
 *  Optimized the code to KISS it mode --  Becker Cuéllar 
 * 
 *    Send  out a byte(mask) and read IN 4 pins and mapp properly, the 74595 allows so only use 3 pins for the 3-octaves
 */

const int LED_pin =13;

// The 74HC595 uses a serial communication 
// link which has three pins
const int clock_pin = 9;
const int latch_pin = 10;
const int data_pin = 11;

// Pin Definitions

const int row0 = 8;
const int row1 = 7;
const int row2 = 6;
const int row3 = 5;

    int groupValue0 = 1;
    int groupValue1 = 1;
    int groupValue2 = 1;
    int groupValue3 = 1;



const int BASE_MIDI=48;   // (F on octave-0)

boolean keyPressed[32];
boolean keyPressedPrev[32];
int noteVelocity = 127;
int curKeyCmd, curMIDIKey;

// proper mask for my board
int cur_byte_mask[] = { B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111 };




void setup() {
 
  // set up diode for visual output
  pinMode(LED_pin, OUTPUT);

 // set pins for the move
  pinMode(data_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);

  pinMode(row0, INPUT);
  pinMode(row1, INPUT);
  pinMode(row2, INPUT);
  pinMode(row3, INPUT);

  for (int j=0; j<32;j++)
  {
     keyPressed[j]=false;
     keyPressedPrev[j]=false;
  }
      
  Serial.begin(31250);   // MIDI standard needs this rate

 
  delay(1000); // time to cool down at startup

 
}  // --- end of setup ---

void loop()
{

  
  for (int col = 0; col < 8; col++) 
  {
    
    // shift scan mask to following column
    scanColumn(cur_byte_mask[col]);


    // check if any keys were pressed - rows will have HIGH output when nothing pressed
    groupValue0 = digitalRead(row0);
    groupValue1 = digitalRead(row1);
    groupValue2 = digitalRead(row2);
    groupValue3 = digitalRead(row3);


// since it is an inverted mask is with a '0' scanning a '1' is 

     keyPressed[col]= ( (groupValue0==0) && ( (two_exp_n(col)&cur_byte_mask[col]) == 0) );
     handleSingleKey(col);

     keyPressed[col+8]= ( (groupValue1==0) && ( (two_exp_n(col)&cur_byte_mask[col]) == 0) );
     handleSingleKey(col+8);

     keyPressed[col+16]= ( (groupValue2==0) && ( (two_exp_n(col)&cur_byte_mask[col]) == 0) );
     handleSingleKey(col+16);

     keyPressed[col+24]= ( (groupValue3==0) && ( (two_exp_n(col)&cur_byte_mask[col]) == 0) );
     handleSingleKey(col+24);

    }// for


}  // -- end of  loop --- 


//find which bit has a '0' in this mask - arduino exp didn't work 4 me
int two_exp_n(int this_n_exp)
{
  int ret = 1;
  int i=0;

   for(int k=0; k<this_n_exp; k++)
      ret = ret*2;
      
  return(ret);
  
}  // --- end of bit_pos  ---

//  status byte   0x1001 CCCC  -) status byte(1st bit=1) note=ON on channel CCCC
//  followd by optional data bytes 0PPP PPPP 0VVV VVVV  pitch(actual music keu lije a C) and velocity
//
//    0x90 Note ON on channel 1
//    0x80 Note OFF on channel 1
//
void handleSingleKey(int thisIdx)
{
 
    if( keyPressed[thisIdx] != keyPressedPrev[thisIdx])
    {
        curKeyCmd = keyPressed[thisIdx] ? 0x90 : 0x80; 
        noteOn(curKeyCmd, BASE_MIDI + thisIdx , 127);  
               
        keyPressedPrev[thisIdx] = keyPressed[thisIdx]; 
    }
    
 
}  // --- end of handleSingleKey ---



// ---- my routines to handle the stuff
// 74HC595 shift to next column
void scanColumn(int value) {
  digitalWrite(latch_pin, LOW); //Pulls the chips latch_pin low
  shiftOut(data_pin, clock_pin, MSBFIRST, value); //Shifts out the 8 bits to the shift register
  digitalWrite(latch_pin, HIGH); //Pulls the latch_pin high displaying the data_pin
}




//
//  Midi msg:   [cmd] [data1] [data2]
//
//  basic midi: cmd   = 100K cccc (cccc is the channel 0-based)   , K=1 note ON , K=0 note OFF
//              data1 = 0ppp pppp (the pitch 0-127)  , middle C is 60
//              data2 = 0vvv vvvv (velocity 0-127 or haw hard is pressed) 
//
void noteOn(int cmd, int pitch, int velocity)  // make MID message , velocity specifies haw hard was the key pressed(0-127)
{

  
    Serial.write(cmd);
   Serial.write(pitch);
   Serial.write(velocity);
}


}

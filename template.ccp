void loop()
{
 byte pA5, pA4, pA3, pA2, pA1;
 int pA0;
 int pbend;
 // illuminate the keys to press next
 lightup(nextvalue);
 // reads the tuning potentiometer and determines what the tuning factor is
 pA0 = analogRead(A0);
 // the raw pA0 value is 0..1024, convert to 0..500
 pbend = (pA0 / 1024.0) * 500;
 // manual fudge factor, even when turned all the way down it read 33, so we subtract that
 pbend -= 33;
 //Serial.println(pbend);
 // turn off all the key lights
 alloff();
 // update the high score on the LCD screen
 lcd.setCursor(0, 1);
 lcd.print(highscore);
 //lcd.print(millis() / 1000);
 //lcd.scrollDisplayLeft();
 // read all the keys simultaneously
 // not pressed returns 1, pressed returns 0
 pA5 = digitalRead(A5);
 pA4 = digitalRead(A4);
 pA3 = digitalRead(A3);
 pA2 = digitalRead(A2);
 pA1 = digitalRead(A1);
 // for scoring purposes, convert keys to same value in song array
 // convert each key to a power of 2 (1,2,4,8,16) by multiplying it, then add all the keys.
 // unused keys show up as fixed values 32,64,128
 // since keys not pressed return 1, if nothing is pressed, this will return 255
 // The song array uses 0 when nothing is pressed so invert the final result (~)
 byte v = ~(pA1 * 1 + pA2 * 2 + pA3 * 4 + pA4 * 8 + pA5 * 16 + 32 + 64 + 128);
 Serial.println(v);
 // wait for keys to be pressed
 if (v != 0)
 {
   // if we are waiting for the next note
   if (nextvalue != 0)
   {
     // and it matches the played note
     if (v == nextvalue)
     {
       // force the else section on the topmost if to be taken next time to load the next note
       // and increment the highscore
       nextvalue = 0;
       highscore++;
     }
     else
     {
       // played note does not match the one we are waiting for, reset high score and clear lcd
       highscore = 0;
       lcd.setCursor(0, 1);
       lcd.print("          ");
     }
   }
 }
 else
 {
   // load the next note
   if (nextvalue == 0)
   {
     nextvalue = song1[songstep];
     songstep++;
     // if song is over, re-start from begining
     if (songstep > song1[0])
     {
       songstep = 1;
     }
   }
 }
 // slightlyt repetitive section to detect if a key was just pressed.
 // (0 is pressed, 1 is not pressed)
 if (pA5 == 0)
 {
   // if this flag is 0, the key was not pressed last time we were here
   // i.e. this is the first time it is pressed
   if (ppA5 == 0)
   {
     // change the flag to 1 to ignore it until it is released
     ppA5 = 1;
     // and play the corresponding note using the Round Robin Algorithm
     play(freqs[4] + pbend);
   }
 }
 else
 {
   // once the key is released, clear the flag
   // so next time the key is pressed the note will play
   ppA5 = 0;
 }
...

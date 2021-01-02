/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("ready.");
  
}

// low bit  : HIGH: HIGHSIGus, LOWGAPus LOW
// start bit: HIGH: HIGHSIGus, HIGHGAPus LOW
// high bit : HIGH: HIGHSIGus, 553us LOW

// proto:
/*
START : 1

TOGGLE: 1
ESC:    0
CH:     00

ADD:    0
MODE:   001

DATA:   0101

LCRC: 0xF xor Nibble1 xor Nibble2 xor Nibble3
= 3
STOP: 1

payload:
1000 0001 0101 0011
*/

const unsigned long HIGHSIG = 156UL;

const unsigned long HEADERGAP = 1014UL;

const unsigned long LOWGAP = 260UL;

const unsigned long HIGHGAP = 546UL;

void sendNibble(byte nibble, int pin){
  for (byte mask = 8; mask!=0; mask >>= 1){
    if (mask & nibble) {
      high(HIGHSIG, 38, pin);
      wait(HIGHGAP);
    }
    else {
      high(HIGHSIG, 38, pin);
      wait(LOWGAP);
    }
  } 
}

void sendSeq(byte nib1, byte nib2, byte nib3, int pin){

  unsigned long t = micros();

  byte lcrc = 15 ^ nib1 ^ nib2 ^ nib3;
  // start bit  
  high(HIGHSIG, 38, 13);
  wait(HEADERGAP);

  sendNibble(nib1, 13);
  sendNibble(nib2, 13);
  sendNibble(nib3, 13);
  sendNibble(lcrc, 13);  
 
  /* 
  for (byte mask = 128; mask!=0; mask >>= 1){  
//  for (byte mask = 0x01; mask; mask <<= 1){
    if (mask & seqHigh) {
      high(HIGHSIG, 38, 13);
      wait(HIGHGAP);
    }
    else {
      high(HIGHSIG, 38, 13);
      wait(LOWGAP);
    }
    
  }
  */
  // stop bit
  high(HIGHSIG, 38, 13);
  wait(HEADERGAP);
  
  
  Serial.println(t);
  // stop bit
}


void wait(unsigned int time){
  unsigned long start = micros();
  while(micros()-start<=time){
  }
}

void high(unsigned int time, int freq, int pinLED){
  int pause = (1000/freq/2)-4;
  unsigned long start = micros();
  while(micros()-start<=time){
    digitalWrite(pinLED,HIGH);
    delayMicroseconds(pause);
    digitalWrite(pinLED,LOW);
    delayMicroseconds(pause);
  }
}

void acc(){
  sendSeq(B0100, B0001, B1111, 13);
  delay(300);
  sendSeq(B0100, B0010, B1111, 13);
  delay(300);
  sendSeq(B0100, B0011, B1111, 13);
  delay(300);
  sendSeq(B0100, B0100, B1111, 13);
  delay(300);
  sendSeq(B0100, B0101, B1111, 13);
  delay(300);
  
  sendSeq(B0100, B0111, B1001, 13);
  delay(300);
  sendSeq(B0100, B0111, B1001, 13);
  delay(300);
  sendSeq(B0100, B0111, B1001, 13);
  delay(300);
  sendSeq(B0100, B0011, B1001, 13);
  delay(300);
  sendSeq(B0100, B0011, B1001, 13);
  delay(300);
  sendSeq(B0100, B1011, B1001, 13);
  delay(300);
  sendSeq(B0100, B1011, B1001, 13);
  delay(300);
  
  
}

void dec(){
  sendSeq(B0100, B0001, B1111, 13);
  delay(300);
  sendSeq(B0100, B1000, B1000, 13);
  delay(300);
}
// the loop function runs over and over again forever
void loop() {
  //1000 0001 0101 0011

  //sendSeq(B1000, B0001, B0101, 13);
  //sendSeq(B0100, B0001, B1111, 13);
  acc();
  delay(3000);
  
}

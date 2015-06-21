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

const int HIGHSIG = 156;

const int HEADERGAP = 1014;

const int LOWGAP = 260;

const int HIGHGAP = 546;

void irStartStop(){
  digitalWrite(13, HIGH);
  delayMicroseconds(HIGHSIG);
  digitalWrite(13, LOW);
  delayMicroseconds(HEADERGAP);
}

void irLow(){
  digitalWrite(13, HIGH);
  delayMicroseconds(HIGHSIG);
  digitalWrite(13, LOW);
  delayMicroseconds(LOWGAP);
}

void irHigh(){
  digitalWrite(13, HIGH);
  delayMicroseconds(HIGHSIG);
  digitalWrite(13, LOW);
  delayMicroseconds(HIGHGAP);
}

void irSend(){
  
  // start
  irStartStop();
  // 1000 0001 0101 0011
  irHigh();
  //irLow();
  irLow();
  irLow();    
  irLow();
  
  irLow();
  irLow();
  irLow();
  irHigh();
  
  irLow();
  irHigh();
  irLow();
  irHigh();
  
  irLow();
  irLow();
  irHigh();
  irHigh();
  // stop:
  irStartStop();  
}
// the loop function runs over and over again forever
void loop() {
  irSend();
  delay(400);
}

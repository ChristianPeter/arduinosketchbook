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


void sendSeq(unsigned int seq, int pin){

  unsigned long t = micros();

  // start bit  
  high(HIGHSIG, 38, 13);
  wait(HEADERGAP);

  //1000 0001 0101 0011
  //1000
  high(HIGHSIG, 38, 13);
  wait(HIGHGAP);
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  
  // 0001
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(HIGHGAP);
  
  // 0101
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(HIGHGAP);
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(HIGHGAP);
  
  // 0011
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(LOWGAP);
  high(HIGHSIG, 38, 13);
  wait(HIGHGAP);
  high(HIGHSIG, 38, 13);
  wait(HIGHGAP);
    
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

// the loop function runs over and over again forever
void loop() {
  sendSeq(128, 13);
  delay(1000);
}

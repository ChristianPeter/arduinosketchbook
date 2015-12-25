
const byte irpin = 3;
const byte TRIGGER = 4;
const byte ECHO = 2;
const byte FTRIGGER = 5;
const byte FECHO = 6;

const byte LEFT = 7;
const byte FORWARDS = 7;
const byte NEUTRAL = 8;
const byte RIGHT = 9;
const byte BACKWARDS = 9;
const int DELAY = 300;

double distance = 0.0;
double fdistance = 0.0;


void setup() {
  
  pinMode(irpin, OUTPUT);  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(FTRIGGER, OUTPUT);
  pinMode(FECHO, INPUT);
  
  digitalWrite(TRIGGER, LOW);
  digitalWrite(FTRIGGER, LOW);
  // TRIGGER muss mindestens 2µs LOW sein
  delayMicroseconds(2);
  
  Serial.begin(57600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("LegoCrawler: ready.");
  
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
  high(HIGHSIG, 38, pin);
  wait(HEADERGAP);

  sendNibble(nib1, pin);
  sendNibble(nib2, pin);
  sendNibble(nib3, pin);
  sendNibble(lcrc, pin);  
 
  // stop bit
  high(HIGHSIG, 38, pin);
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
  sendSeq(B0100, B0001, B1111, irpin);
  delay(300);
  sendSeq(B0100, B0010, B1111, irpin);
  delay(300);
  sendSeq(B0100, B0011, B1111, irpin);
  delay(300);
  sendSeq(B0100, B0100, B1111, irpin);
  delay(300);
  sendSeq(B0100, B0101, B1111, irpin);
  delay(300);
  
  sendSeq(B0100, B0111, B1001, irpin);
  delay(300);
  sendSeq(B0100, B0111, B1001, irpin);
  delay(300);
  sendSeq(B0100, B0111, B1001, irpin);
  delay(300);
  sendSeq(B0100, B0011, B1001, irpin);
  delay(300);
  sendSeq(B0100, B0011, B1001, irpin);
  delay(300);
  sendSeq(B0100, B1011, B1001, irpin);
  delay(300);
  sendSeq(B0100, B1011, B1001, irpin);
  delay(300);
  
  
}

void dec(){
  sendSeq(B0100, B0001, B1111, irpin);
  delay(300);
  sendSeq(B0100, B1000, B1000, irpin);
  delay(300);
}


void drive(byte a, byte b){
  Serial.print("drive: ");
  Serial.print(a);
  Serial.print(":");
  Serial.println(b);
  sendSeq(B0100, a, b, irpin);
}

void driveBW(byte s){
  drive(s,16-s);
}

void driveFW(byte s){
  drive(16-s,s);
}

void driveStop(){
  drive(0,0);
} 

void turnLeft(byte s){
  drive(16-s,16-s);
}

void turnRight(byte s){
  drive(s,s);
}

// distance checks:

double sonic(byte t, byte e){
    long laufzeit;
    double entfernung;
    // Einen Impuls auslösen
    digitalWrite(t, HIGH);
    delayMicroseconds(5);
    digitalWrite(t, LOW);

    // Messen, wann der reflektierte Impuls zurückkommt
    laufzeit = pulseIn(e, HIGH);

    // Pro Meter benötigt der Schall in Luft ca. 2,9 ms
    // pulseIn misst Mikrosekunden, also 2,9 µs pro Millimeter
    // Weg geht hin und zurück, also mal 2
    entfernung = (double) laufzeit / (2.9 * 2.0);
    
    return entfernung;
}



// the loop function runs over and over again forever
unsigned long counter = 0;
byte cSpeed = BACKWARDS;
byte cDir = NEUTRAL;

void drive(){
  drive(cDir,cSpeed);
  delay(DELAY);
}

void stopBackwards(){
  cSpeed = NEUTRAL;
  drive();
  cSpeed = FORWARDS;
  cDir = cDir == LEFT? RIGHT: LEFT;
}

void stopForwards(){
  cSpeed = NEUTRAL;
  cDir = NEUTRAL;
  drive();
  cSpeed = BACKWARDS;
}

void loop(){
  counter++;
  distance = sonic(TRIGGER, ECHO);
  fdistance = sonic(FTRIGGER, FECHO);
  
  Serial.print("Entfernung zum Objekt back: ");
  Serial.print(distance);
  Serial.println(" mm");
  Serial.print("Entfernung zum Objekt front: ");
  Serial.print(fdistance);
  Serial.println(" mm");
  
  if (cSpeed == NEUTRAL){
    if (fdistance > 500){
      cSpeed = FORWARDS;
    }
  }
  if (cSpeed == BACKWARDS){
    if (distance < 150){
      stopBackwards();
    }
  }
  if (cSpeed == FORWARDS){
    if (fdistance < 150){
      stopForwards();
    }
  }
/*  
  if (random(100) > 90){
    cDir = cDir == LEFT? RIGHT: LEFT;
    counter = 0;
  }
  */
  /*
  if (counter > 10) {
    cDir = NEUTRAL;
  }*/
    
  
  drive();  

}
void loop_old() {
  counter++;
  //1000 0001 0101 0011

  //sendSeq(B1000, B0001, B0101, irpin);
  //sendSeq(B0100, B0001, B1111, irpin);
  //acc();
  
  //driveFW(7);
  //turnRight(2);
  
  distance = sonic(TRIGGER, ECHO);
  
  
  if (distance < 150) {    
    driveStop();
    delay(DELAY);
    driveBW(3);
    delay(DELAY);
    driveBW(5);
    delay(DELAY);
    driveBW(7);
    delay(DELAY);
    if (random(300) > 150){
      turnRight(7);
      delay(DELAY + random(DELAY)*5);
      turnRight(7);
    }
    else {
      turnLeft(7);
      delay(DELAY +random(DELAY)*5);
      turnLeft(7);
    }
    delay(DELAY); 
    cSpeed = 0;    
  }
  driveFW(cSpeed);
  delay(DELAY);
  
  if (cSpeed <7) cSpeed ++;
  
  if (counter % 10 == 0 && random(100) > 90) {
    cSpeed = 0;
    driveStop();
    delay(DELAY);
    if (random(300) > 150){
      turnRight(7);
      delay(DELAY + random(DELAY)*5);
      turnRight(7);
    }
    else {
      turnLeft(7);
      delay(DELAY +random(DELAY)*5);
      turnLeft(7);
    }
    delay(DELAY);
    
  } 
}

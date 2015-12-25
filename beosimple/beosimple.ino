const int TVbuttonPin = 4;
const int BEO_IR =  13;

int TVbuttonState = 0;

void setup() {
  pinMode(BEO_IR, OUTPUT);      
  pinMode(TVbuttonPin, INPUT);     
}


void transmit(){
 digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(3125);  // start bit 1
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(3125);  // start bit 2
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(15625); // start bit 3
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(3125);  // start bit 4
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 01: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 02: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 03: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 04: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 05: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 06: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 07: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 08: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(9375);  // data bit 09: 1 bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(3125);  // data bit 10: 0 bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 11: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 12: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 13: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 14: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 15: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(6250);  // data bit 16: repeat bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); delayMicroseconds(12500); // trailer bit
    digitalWrite(BEO_IR, HIGH); delayMicroseconds(200); digitalWrite(BEO_IR, LOW); 

}
void loop(){
  TVbuttonState = digitalRead(TVbuttonPin);

  if (TVbuttonState == HIGH) {   
    transmit();
  }
  
}

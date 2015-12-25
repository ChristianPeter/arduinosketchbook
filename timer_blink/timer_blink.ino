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
#define CLR(x,y) (x&=(~(1<<y)))

#define SET(x,y) (x|=(1<<y))

#define _BV(bit) (1 << (bit))

#define D13high | 0x20; 
#define D13low  & 0xDF; 

boolean toggle0 = 0;
boolean toggle1 = 0;
boolean sendHigh = 0;

int payload[] = {3125 ,3125 ,15625 ,3125 ,6250 ,6250 ,6250 ,6250 ,6250 ,6250 ,6250 ,6250 ,6250 ,9375 ,6250 ,3125 ,6250 ,6250 ,6250 ,6250 ,12500};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, INPUT);
  digitalWrite(9,HIGH);

/*
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
*/
  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 34;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  //TCCR1B |= (1 << CS12) | (1 << CS10);  
  TCCR1B |= (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
  
}
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (sendHigh){
    if (toggle1){
      //digitalWrite(13,HIGH);
      //PORTB &= ~(_BV(1));
      PORTB = PORTB D13high;

      toggle1 = 0;
    }
    else{
      //digitalWrite(13,LOW);
      //PORTB |= _BV(1);
      PORTB = PORTB D13low;
      toggle1 = 1;
    }
  }
}


void wait(unsigned int time){
  unsigned long start = micros();
  while(micros()-start<=time){
  }
}


void sendPayload(){
  for (int i = 0; i < (sizeof(payload)/sizeof(int)) - 1; i++) {
    //digitalWrite(9,LOW);
    sendHigh = 0;
    wait(200);
//    digitalWrite(9,HIGH);
    sendHigh = 1;
    wait(payload[i]);
  }
  
  sendHigh = 0;
}

long mics = 0;
// the loop function runs over and over again forever
void loop() {
  
  sendHigh = 0;
  int v = digitalRead(4);
  if (v == HIGH){
  //  Serial.println("send");
    mics = micros();    
    sendPayload();
    while (micros() - mics < 10000){}
  //  Serial.println("done");
  }
  
  /*
  digitalWrite(9,LOW);
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
  */
}

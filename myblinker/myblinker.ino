
int led1 = 10;
int led2 = 7;
int led3 = 5;
int led4 = 2;

int leds[] = {led1,led2,led3,led4};
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}


int waittime = 100;


void advent4() {
  for (int i=0; i< 4; i++) {
    digitalWrite(leds[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(waittime);                       // wait for a second
    digitalWrite(leds[i], LOW);   // turn the LED on (HIGH is the voltage level)
    delay(waittime);            
    digitalWrite(leds[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(waittime);            
  }

  delay(4000);

  for (int i=0; i< 4; i++) {
    digitalWrite(leds[3-i], LOW);    // turn the LED off by making the voltage LOW
    delay(waittime);                       // wait for a second
  }

  delay(2000);
}

void random1() {
  int current = random(4);
  int mode = random(10);

  if (mode >=5) {
      digitalWrite(leds[current], HIGH);
  }
  else {
    digitalWrite(leds[current], LOW);  
  }

  delay(waittime);
}

// the loop function runs over and over again forever
void loop() {

  advent4();
  /*

  for (int i=0; i< 4; i++) {
    digitalWrite(leds[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(waittime);                       // wait for a second
  }

  for (int i=0; i< 4; i++) {
    digitalWrite(leds[i], LOW);    // turn the LED off by making the voltage LOW
    delay(waittime);                       // wait for a second
  }*/
}

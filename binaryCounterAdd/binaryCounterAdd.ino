
int pins[] = {2,3,4,5,6,7,8,9};
int numberOfPins = 8;
byte count = 0;
int lastMode = HIGH;

void setup(){
  for (int i = 0; i < numberOfPins; i++){
    pinMode(pins[i], OUTPUT);
  }
  pinMode(12, INPUT);
}

void loop(){
  if (digitalRead(12) == LOW) {
     if (lastMode == HIGH){
       count++;
       lastMode = LOW;
     }
  }
  else{
    lastMode = HIGH;
  }
  
  printByte(count);
  delay(50);
}

void printByte(byte num){
  for (int i = 0; i < numberOfPins; i++){
    if (num & 1 == 1) {
      digitalWrite(pins[i], HIGH);
    }
    else {
      digitalWrite(pins[i], LOW);
    }
    num = num >> 1;
  }
}

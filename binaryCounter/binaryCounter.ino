
int pins[] = {2,3,4,5,6,7,8,9};
int numberOfPins = 8;
byte count = 0;

void setup(){
  for (int i = 0; i < numberOfPins; i++){
    pinMode(pins[i], OUTPUT);
  }
}

void loop(){
  count ++;
  
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

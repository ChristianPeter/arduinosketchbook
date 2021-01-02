
int pins[] = {2,3,4,5,6,7,8,9};
int numberOfPins = 8;

void setup(){
  for (int i = 0; i < numberOfPins; i++){
    pinMode(pins[i], OUTPUT);
  }
}

void loop(){
  for (int i = 0; i < numberOfPins; i++){
    digitalWrite(pins[i], HIGH);
    delay(500);
    digitalWrite(pins[i], LOW);
  }
}

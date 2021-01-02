int motorPins[] = {5,9,10,11};
int currentStep = 0;
int motorDelay = 5;
int dir = 0;
boolean isRunning = false;
int count =0;

void setup() {
  for (int i = 0; i < 4; i++){
    pinMode(motorPins[i], OUTPUT);
  }
  
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}


void step(){
  digitalWrite(13, currentStep % 2 == 0? HIGH: LOW);
  
  if (dir == 0){
    for (int i = 0; i < 4; i++){
      digitalWrite(motorPins[i], i == currentStep ? HIGH:LOW);
    }
  }
  else {
    for (int i = 0; i < 4; i++){
      digitalWrite(motorPins[3-i], i == currentStep ? HIGH:LOW);
    }
  }
  delay(motorDelay);
  currentStep ++;
  if (currentStep > 3) currentStep = 0;
}
void loop() {
  
  int v1 = digitalRead(2);
  int v2 = digitalRead(3);
  int a0 = analogRead(0);
  
  motorDelay = map(a0, 0, 1023, 1, 100);  
  
  if (v1 == LOW){
    isRunning = !isRunning;
    delay(200);
  }
  
  if (v2 == LOW){
    dir = dir == 0? 1:0;
    delay(200);
  }
  
  if (isRunning){
    step();
  }  
  
}

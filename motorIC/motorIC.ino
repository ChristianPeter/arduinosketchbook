int motorA = 6;
int motorB = 5;
int motorSpeed = 3;
int startStop = 9;
int dir = 8;

boolean clockWise = true;
boolean isStarted = true;

int selectedSpeed = 255;


void speedUp(int s){
  for (int i=0; i <= s; i++){
    analogWrite(motorSpeed, i);
    delay(5);
  }
}

void slowDown(int s){
  for (int i=s; i >= 0; i--){
    analogWrite(motorSpeed, i);
    delay(5);
  }
}

void changeDirection(){
  if (isStarted) slowDown(selectedSpeed);
  clockWise = !clockWise;
  setDirection();
  if (isStarted) speedUp(selectedSpeed);
}

void setDirection(){
  if (clockWise) {
    digitalWrite(motorB, HIGH);
    digitalWrite(motorA, LOW);
  }
  else {
    digitalWrite(motorB, LOW);
    digitalWrite(motorA, HIGH);
  }
}
void setup() {
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(startStop, INPUT);
  pinMode(dir, INPUT);
  analogWrite(motorSpeed, selectedSpeed);
  setDirection();
}


void loop() {
  

  if (digitalRead(dir) == LOW){
    changeDirection();    
  }
  
  if (digitalRead(startStop) == LOW){
    if (isStarted){
      slowDown(selectedSpeed);
    }
    else {
      speedUp(selectedSpeed);
    }
    isStarted = !isStarted;
    
  }
  
  
  
  
  if (isStarted) {
    int a = analogRead(0);
    selectedSpeed = map(a, 0, 1023, 0, 255);
    analogWrite(motorSpeed, selectedSpeed);
  }
  
  
  delay(20);

}


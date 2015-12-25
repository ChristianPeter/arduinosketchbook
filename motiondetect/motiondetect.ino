int pirPin = 9;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(pirPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int pirVal = digitalRead(pirPin);

  if(pirVal == LOW){ //was motion detected
    Serial.println("Motion Detected"); 
    delay(2000); 
  }
}




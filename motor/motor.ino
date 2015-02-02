void setup() {
  // put your setup code here, to run once:
  pinMode(9,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly: 
  int pot = map(analogRead(0),0,1024,0,255);
  analogWrite(9,pot);
  delay(1000);
}

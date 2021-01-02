void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
}

void play(int d){
  digitalWrite(13,HIGH);

  delayMicroseconds(d);
  digitalWrite(13, LOW);
  delayMicroseconds(d);
}
void loop() {
  // put your main code here, to run repeatedly: 
  int t = analogRead(0);
  int lfo = analogRead(1);
  for (int i = (lfo/10); i>0; i--){
    play(t);
  }
  
  delayMicroseconds(lfo);
  
  for (int i = 0; i < lfo/10; i++){
    play(t);
  }
}

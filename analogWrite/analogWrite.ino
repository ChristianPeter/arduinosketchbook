void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

int count = 0;
void loop() {
  // put your main code here, to run repeatedly: 
  count ++;
  
  /*analogWrite(9, count % 255);
  analogWrite(10, (count / 256) % 255);
  analogWrite(11, (count / 65536) % 255);
  */
  
  analogWrite(9, (int) (sin(count / 100.) *128) +128);
  analogWrite(10, (int) (sin(count / 125.) *128) +128);
  analogWrite(11, (int) (sin(count / 75.) *128) +128);
  delayMicroseconds(200);
}

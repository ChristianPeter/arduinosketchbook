int rows[8] = {9,3,2,12,15,11,7,6};
int cols[8] = {13,8,17,10,5,16,4,14};
int pinUp = 18;
long count = 0;
int screen[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0
};

// game data
byte px = 4;
byte py = 7;

void drawScreen(){
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 8; x++){    
      digitalWrite(cols[x], screen[x*8+y] == 1 ? HIGH : LOW);      
    }
    digitalWrite(rows[y], LOW);    
    delayMicroseconds(100);    
    digitalWrite(rows[y], HIGH);
  }
}

void putPixel(byte x, byte y, byte c){
  screen[y*8+x] = c;
}

void doSomething(){
  
  count++;
  if (count %100 == 0){
    byte temp = screen[0];
    for (int i = 0 ; i < 64 ; i++){
      screen[i]=screen[(i+1) % 64];
    }
    screen[63] = temp;
  }
}

void drawPlayer(){
  putPixel(px, py, 1);
}

void loop(){
  if (digitalRead(pinUp) == LOW){
    doSomething();
  }
  drawScreen();
 
}


void clearScreen(){
  for (int i=0; i < 64; i++) screen[i] = 0;
}


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; i++){
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
    digitalWrite(cols[i], LOW);
    digitalWrite(rows[i], LOW);
  }
  
  pinMode(pinUp, INPUT);
  
  clearScreen();
  drawPlayer();
  
}


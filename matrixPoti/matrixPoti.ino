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

struct Snow {
  int x;
  int y;
  int cx;
  int cy;
};

Snow snow[10];

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

void drawSnow(){
  for (int i = 0; i < 10; i ++){
    putPixel(snow[i].x / 10 ,snow[i].y / 10,1);
  }
}

void moveSnow(){
  for (int i = 0; i < 10; i ++){
    //snow[i].x += snow[i].cx;
    snow[i].y += snow[i].cy;
    snow[i].cx += (random(2)-1);
  }
}
void putPixel(byte x, byte y, byte c){
  screen[(y%8)*8+(x%8)] = c;
}

void doSomething(){
  
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

void undrawPlayer(){
  putPixel(px, py, 0);
}

void loop(){
  count++;
  //undrawPlayer();
  handlePoti();
  clearScreen();
  drawSnow();
  if (count % 50 == 0 ) {
    moveSnow();    
  }
  
  drawPlayer(); 
  drawScreen();
 
}

void handlePoti(){
  int poti = map(analogRead(pinUp),0,1023,0,7);
  /* 
  if (poti < 512) {
    px++;
  }
  else { 
    px--;
  }
  if (px < 0) px = 0;
  if (px > 7) px = 7;   
  */
  px = poti;
}

void clearScreen(){
  for (int i=0; i < 64; i++) screen[i] = 0;
}


void initSnow(){
  for (int i = 0; i < 10; i ++){
    snow[i].x = random(80);
    snow[i].y = random(20); // on top
    snow[i].cx = random(1)-1; // let it drift a bit
    snow[i].cy = random(3)+1;
  }
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

  initSnow();  
  clearScreen();
  drawPlayer();
  
}


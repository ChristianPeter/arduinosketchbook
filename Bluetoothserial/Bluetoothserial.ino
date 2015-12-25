#include <LiquidCrystal.h>
/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
LiquidCrystal lcd(7,6,5,4,3,2);

byte pos = 0;
unsigned long counter = 0;
byte bufferPos = 0;


void startAlert(){
  digitalWrite(13, HIGH);
}

void stopAlert(){
  digitalWrite(13, LOW);
}

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  /*
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");
  */
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
  pinMode(13, OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("ready.");
  
  counter = millis();
}

int rin = 0;
char buffer [32];
void loop() // run over and over
{

  
  while (mySerial.available() >0){
    rin = mySerial.available();
    //lcd.print(rin);
    buffer[bufferPos++] = mySerial.read();
  }
  if(bufferPos >0){
    //buffer[bufferPos++] = '\0'; // null terminate string
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("received.");
    lcd.setCursor(0,1);
    //lcd.print(bufferPos);
    Serial.write(buffer, bufferPos);
    for (byte i = 0; i < bufferPos; i++){
      lcd.print(buffer[i]);
    }    
    
    if (buffer[0] == '1')  {
      startAlert();
    }
    if (buffer[0] == '0')  {
      stopAlert();
    }
    bufferPos = 0;
    lcd.setCursor(0,0);
    lcd.print("ready.");
  }
  

  if (Serial.available()){
    mySerial.write(Serial.read());
  }
}


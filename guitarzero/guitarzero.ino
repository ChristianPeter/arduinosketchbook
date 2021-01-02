#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10,11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


void setup() {

  pinMode(2, INPUT);
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);

  Serial.println();
  Serial.println(F("Guitar Zero"));
  Serial.println(F("Initializing ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("Guitar Zero online."));

  myDFPlayer.setTimeOut(500);
  myDFPlayer.volume(30);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);


}

void loop() {

  if (digitalRead(2) == HIGH) {
    int p = random(10);
    myDFPlayer.play(7);
    delay(200);  
  }

  delay(100);


  
  /*int p = random(10);
  myDFPlayer.play(p);
  delay(1000);
  */

}

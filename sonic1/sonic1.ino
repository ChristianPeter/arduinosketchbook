/*
  Arduino <-> Ultraschallsensor HC SR04
  -------------------------------------
  
  Erzeugt einen Ultraschallimpuls und misst die Zeit,
  bis das Echo aufgefangen wird. Aus der Laufzeit des
  Schallimpulses wird die Entfernung zum reflektierenden
  Objekt berechnet.
 
*/

// Trig ist an Digital-Pin 7 angeschlossen
const byte TRIGGER = 4;

// und Echo an Digital-Pin 8
const byte ECHO = 2;

/************************************************************
*
* void setup()
* ------------
*
* Wird einmal beim Programmstart durchlaufen
*
*************************************************************/
void setup() {                
  Serial.begin(9600);   

  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  // Damit später durch HIGH-setzen von TRIGGER ein Impuls
  // ausgelöst werden kann, wird TRIGGER hier LOW gesetzt.
  digitalWrite(TRIGGER, LOW);

  // TRIGGER muss mindestens 2µs LOW sein
  delayMicroseconds(2);

  // Für Leonardo
  while (!Serial)
    ;  
}

/************************************************************
*
* void loop()
* ------------
*
* Wird immer wieder durchlaufen
*
*************************************************************/
void loop() {
  long laufzeit;
  double entfernung;

  while(true) {
    // Einen Impuls auslösen
    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(5);
    digitalWrite(TRIGGER, LOW);

    // Messen, wann der reflektierte Impuls zurückkommt
    laufzeit = pulseIn(ECHO, HIGH);

    // Pro Meter benötigt der Schall in Luft ca. 2,9 ms
    // pulseIn misst Mikrosekunden, also 2,9 µs pro Millimeter
    // Weg geht hin und zurück, also mal 2
    entfernung = (double) laufzeit / (2.9 * 2.0);

    Serial.print("Entfernung zum Objekt: ");
    Serial.print(entfernung);
    Serial.println(" mm");

    delay(100);
  }
}

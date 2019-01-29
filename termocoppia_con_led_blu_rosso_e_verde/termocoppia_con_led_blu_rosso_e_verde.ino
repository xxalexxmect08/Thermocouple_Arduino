// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"

unsigned long old_millis = 0;
unsigned long delta = 1000;
int minuti = 1;

int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;
int ledPin = 8; // led  blu
int maxtemp = 12; // led rosso
int mintemp = 13; // led verde

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

void setup() {
  Serial.begin(9600);
  // use Arduino pins
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  pinMode (ledPin, OUTPUT);
  pinMode (maxtemp, OUTPUT);
  pinMode (mintemp, OUTPUT);
  Serial.println("MAX6675 test");

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp

  unsigned long now = millis () ; // variabile
  if (now > old_millis + delta) { //se il tempo attuale
    Serial.print (minuti);
    Serial.print (",");
    Serial.println(thermocouple.readCelsius());
    old_millis = now; // terminato il ciclo pone il valore
    minuti = minuti + 1; // incrementa il contatoredi minuti
    digitalWrite (ledPin, HIGH);
    delay (350);
    digitalWrite (ledPin, LOW);

    if (thermocouple.readCelsius() > 50) {
      digitalWrite(maxtemp, HIGH);
    }
    if (thermocouple.readCelsius() < 45) {
      digitalWrite(maxtemp, LOW);
    }



    if (thermocouple.readCelsius() < 35) {
      digitalWrite (mintemp, HIGH);
    }
    if (thermocouple.readCelsius () > 40) {
      digitalWrite (mintemp, LOW);
    }
  }
  delay(10); //pausa nell' esecuzione del ciclo
}

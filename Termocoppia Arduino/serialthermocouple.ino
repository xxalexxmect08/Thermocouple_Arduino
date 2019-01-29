// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"
unsigned long old_millis = 0;
unsigned long delta = 60000;
int minuti = 1;
int ledPin = 8;
int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

void setup() {
  Serial.begin(9600);
  // use Arduino pins
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  pinMode(ledPin, OUTPUT);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {

  unsigned long now = millis();

  if (now > old_millis + delta) {
    Serial.print(minuti);
    Serial.print(" , ");
    Serial.println(thermocouple.readCelsius());
    old_millis = now;
    minuti = minuti + 1;
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
  delay(1);
}

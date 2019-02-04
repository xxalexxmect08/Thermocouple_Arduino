// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include "max6675.h"
unsigned long old_millis = 0;
unsigned long delta = 1000;
int minuti = 1;
int ledPin = 8;
int ledMax = 12;
int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);



void setup() {
  Serial.begin(9600);
  // use Arduino pins

  pinMode(ledPin, OUTPUT);
  pinMode(ledMax, OUTPUT);

  dht.begin();

  Serial.println("Time,°C Termocoppia,°C DHT11,°C temp percepita");

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {

  delay(2000);

    unsigned long now = millis();
  float T_thermo = thermocouple.readCelsius();

  if (now > old_millis + delta) {
    //Serial.print("Termocoppia: ");
    Serial.print(minuti);
    Serial.print(",");
    //Serial.print(" , ");
    Serial.print(T_thermo);
    Serial.print(",");
    //Serial.print(" °C ");
    float h = dht.readHumidity();
  float T_DHT11 = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(T_DHT11, h, false);

  //Serial.print("DHT11: ");
  //Serial.print(F("Humidity: "));
  //Serial.print(h);
  //Serial.print(",");
  //Serial.print(F(" %  Temperature: "));
  Serial.print(T_DHT11);
  Serial.print(",");
  //Serial.print(F(" °C "));
  //Serial.print(F("  Heat index: "));
  Serial.println(hic);
  //Serial.println(F(" °C "));
    old_millis = now;
    minuti = minuti + 1;
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }

  if (T_thermo < 40 && T_thermo > 35) {
    digitalWrite(ledMax, HIGH);
  }
  if (T_thermo > 40 || T_thermo < 35) {
    digitalWrite(ledMax, LOW);
  }

  


  delay(1);
}

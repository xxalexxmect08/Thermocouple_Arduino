#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include "max6675.h"
int minuti = 1;
int ledPin = 8;
int ledMax = 12;
int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

int buttonPin = 13;
int laststate = 0;


void setup() {

  Serial.begin (9600);
  pinMode (buttonPin, INPUT) ;
  pinMode (ledPin, OUTPUT);
  pinMode (ledMax, OUTPUT);

  dht.begin();

  Serial.println("Time,°C Termocoppia,°C DHT11,°C temp percepita");

  // wait for MAX chip to stabilize
  delay(1000);
}

void loop() {
  float T_thermo = thermocouple.readCelsius();
  int state = digitalRead (buttonPin);
  if (state == HIGH && state != laststate) {
     digitalWrite(ledPin, HIGH);
    //Serial.println(counter);
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
    digitalWrite(ledPin, LOW);
    //Serial.println(laststate);
  }
  laststate = state;

  if (T_thermo < 40 && T_thermo > 35) {
    digitalWrite(ledMax, HIGH);
  }
  if (T_thermo > 40 || T_thermo < 35) {
    digitalWrite(ledMax, LOW);
  }
  delay (1) ;// delay in between reads for stability
}

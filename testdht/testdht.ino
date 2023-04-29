// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, modified for integer use, public domain

#include "TinyDHT.h"

#define DHTPIN 2 // DHT connected to Arduino Uno Digital Pin 2
#define RAINPIN A0

// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302)
// #define DHTTYPE DHT21   // DHT 21 (AM2301)
const int ENA_PIN = 7; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N

const int IN3_PIN = 3; // the Arduino pin connected to the IN3 pin L298N
const int IN4_PIN = 4; // the Arduino pin connected to the IN4 pin L298N
// Connect pin 1 (on the left) ovf the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power)
//    of the sensor

// kipas
// rain sensor
// suhu dht
// motor slenoid
// timer

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200); // Output status on Uno serial monitor
  Serial.println("DHTxx test!");
  pinMode(2, INPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  digitalWrite(ENA_PIN, HIGH);

  dht.begin();
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int8_t h = dht.readHumidity();
  int16_t t = dht.readTemperature(1);

  int sensorValue = analogRead(RAINPIN);
  int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data

  // check if returns are valid then something went wrong!
  if (t == BAD_TEMP || h == BAD_HUM)
  { // if error conditions
    Serial.println("Failed to read from DHT");
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
    Serial.print(outputValue);
    Serial.println(" rain sensor ");

    if (t >= 30)
    {
      digitalWrite(IN3_PIN, HIGH);
      digitalWrite(IN4_PIN, LOW);
    }
    else
    {
      digitalWrite(IN3_PIN, LOW);
      digitalWrite(IN4_PIN, HIGH);
    }
  }
  delay(2000);
}
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, modified for integer use, public domain

#include "TinyDHT.h"
#include <Wire.h>
// #include <DS3231.h>
#include <time.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

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
// timer sda a4 / scl a5

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
  Wire.begin();

  dht.begin();

   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  int8_t h = dht.readHumidity();
  int16_t t = dht.readTemperature(1);




  DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    if (now.second()%10 == 0)
    {
    Serial.print('10 saat ');

    }
    Serial.print(now.second(), DEC);


    // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));

    Serial.print(" now + 7d + 12h + 30m + 6s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();

 

    Serial.println();


  // int sensorValue = analogRead(RAINPIN);
  // Serial.print(sensorValue);
  // Serial.println(" rain sensor ");

  // if (sensorValue <= 800)
  // {
  //   digitalWrite(IN1_PIN, LOW);
  //   digitalWrite(IN2_PIN, HIGH);
  //   Serial.print("TUTUP");
  // }
  // else
  // {
  //   digitalWrite(IN1_PIN, HIGH);
  //   digitalWrite(IN2_PIN, LOW);
  //   Serial.print("bUKA ");
  // }
  // // check if returns are valid then something went wrong!
  // if (t == BAD_TEMP || h == BAD_HUM)
  // { // if error conditions
  //   Serial.println("Failed to read from DHT");
  // }
  // else
  // {
  //   Serial.print("Humidity: ");
  //   Serial.print(h);
  //   Serial.print(" %\t");
  //   Serial.print("Temperature: ");
  //   Serial.print(t);
  //   Serial.println(" *C");

  //   if (t >= 30)
  //   {
  //     digitalWrite(IN3_PIN, HIGH);
  //     digitalWrite(IN4_PIN, LOW);
  //   }
  //   else
  //   {
  //     digitalWrite(IN3_PIN, LOW);
  //     digitalWrite(IN4_PIN, HIGH);
  //   }
  // }


  delay(2000);
}
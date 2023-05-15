// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, modified for integer use, public domain

#include "TinyDHT.h"
#include <Wire.h>
#include <DS3231.h>
#include <time.h>


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

byte year ;
byte month ;
byte date ;
byte dOW ;
byte hour ;
byte minute ;
byte second ;
bool Century  = false;
bool h12 ;
bool PM ;

DS3231 myRTC;


void getDateStuff(byte &year, byte &month, byte &date, byte &dOW,
                  byte &hour, byte &minute, byte &second)
{
  // Call this if you notice something coming in on
  // the serial port. The stuff coming in should be in
  // the order YYMMDDwHHMMSS, with an 'x' at the end.
  boolean gotString = false;
  char inChar;
  byte temp1, temp2;
  char inString[20];

  byte j = 0;
  while (!gotString)
  {
    if (Serial.available())
    {
      inChar = Serial.read();
      inString[j] = inChar;
      j += 1;
      if (inChar == 'x')
      {
        gotString = true;
      }
    }
  }
  Serial.println(inString);
  // Read year first
  temp1 = (byte)inString[0] - 48;
  temp2 = (byte)inString[1] - 48;
  year = temp1 * 10 + temp2;
  // now month
  temp1 = (byte)inString[2] - 48;
  temp2 = (byte)inString[3] - 48;
  month = temp1 * 10 + temp2;
  // now date
  temp1 = (byte)inString[4] - 48;
  temp2 = (byte)inString[5] - 48;
  date = temp1 * 10 + temp2;
  // now Day of Week
  dOW = (byte)inString[6] - 48;
  // now hour
  temp1 = (byte)inString[7] - 48;
  temp2 = (byte)inString[8] - 48;
  hour = temp1 * 10 + temp2;
  // now minute
  temp1 = (byte)inString[9] - 48;
  temp2 = (byte)inString[10] - 48;
  minute = temp1 * 10 + temp2;
  // now second
  temp1 = (byte)inString[11] - 48;
  temp2 = (byte)inString[12] - 48;
  second = temp1 * 10 + temp2;
}

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
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  if (Serial.available())
  {
    getDateStuff(year, month, date, dOW, hour, minute, second);

    myRTC.setClockMode(false); // set to 24h
    // setClockMode(true); // set to 12h

    myRTC.setYear(year);
    myRTC.setMonth(month);
    myRTC.setDate(date);
    myRTC.setDoW(dOW);
    myRTC.setHour(hour);
    myRTC.setMinute(minute);
    myRTC.setSecond(second);

  Serial.print(" minute set :  ");

  Serial.println(minute, DEC);

  }
  
  int8_t h = dht.readHumidity();
  int16_t t = dht.readTemperature(1);



  Serial.print(myRTC.getYear(), DEC);
  Serial.print("-");
  Serial.print(myRTC.getMonth(Century), DEC);
  Serial.print("-");
  Serial.print(myRTC.getDate(), DEC);
  Serial.print(" ");
  Serial.print(myRTC.getHour(h12, PM), DEC); //24-hr
  Serial.print(":");
  Serial.print(myRTC.getMinute(), DEC);
  Serial.print(":");
  Serial.println(myRTC.getSecond(), DEC);
  delay(1000);

  DateTime currentMoment = RTClib::now();
  Serial.print(" minute 2:  ");

  Serial.print(currentMoment.minute(), DEC);



  Serial.print(" minute :  ");

  Serial.println(myRTC.getMinute(), DEC);

  int sensorValue = analogRead(RAINPIN);
  Serial.print(sensorValue);
  Serial.println(" rain sensor ");

  if (sensorValue <= 800)
  {
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    Serial.print("TUTUP");
  }
  else
  {
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    Serial.print("bUKA ");
  }
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
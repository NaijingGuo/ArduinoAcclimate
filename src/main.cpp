#include <Arduino.h>
#include <CapacitiveSensor.h>
#include <elapsedMillis.h>

elapsedMillis timeElapsed;

CapacitiveSensor cs = CapacitiveSensor(4, 2);

#define BLUE 3
#define GREEN 5
#define RED 6

void pink()
{
  analogWrite(RED, 30);
  analogWrite(BLUE, 25);
  analogWrite(GREEN, 0);
}

void blue()
{
  analogWrite(RED, 10);
  analogWrite(BLUE, 35);
  analogWrite(GREEN, 40);
}

void yellow()
{
  analogWrite(RED, 50);
  analogWrite(BLUE, 10);
  analogWrite(GREEN, 50);
}

void off()
{
  analogWrite(RED, 0);
  analogWrite(BLUE, 0);
  analogWrite(GREEN, 0);
}

void setup()
{
  Serial.begin(9600);
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  yellow();
}

void loop()
{

  int threshold = 100;
  long sensorValue = cs.capacitiveSensor(30);
  Serial.print(sensorValue);

  if (sensorValue > threshold)
  {
    blue();
    timeElapsed = 0;
  }
  if (timeElapsed > 10000) // this is 10s
  {
    pink();
  }
}
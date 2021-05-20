#include <Arduino.h>
#include <CapacitiveSensor.h>

CapacitiveSensor cs = CapacitiveSensor(4, 2);

#define BLUE 3
#define GREEN 5
#define RED 6

char color; // used in switch

void pink()
{
  analogWrite(RED, 30);
  analogWrite(BLUE, 25);
  analogWrite(GREEN, 0);
  color = 'pink';
}

void blue()
{
  analogWrite(RED, 10);
  analogWrite(BLUE, 35);
  analogWrite(GREEN, 40);
  color = 'blue';
}

void yellow()
{
  analogWrite(RED, 50);
  analogWrite(BLUE, 10);
  analogWrite(GREEN, 50);
  color = 'yellow';
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
  blue();
}

void loop()
{

  int threshold = 100;
  long sensorValue = cs.capacitiveSensor(30);
  Serial.print(sensorValue);

  if (sensorValue > threshold)
  {
    pink();
  }
  else
  {
    blue();
  }
  delay(10);
}
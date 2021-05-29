#include <Arduino.h>
#include <CapacitiveSensor.h>
#include <elapsedMillis.h>

elapsedMillis timeElapsed;

CapacitiveSensor cs = CapacitiveSensor(4, 2);
const int buzzer = 9;

#define BLUE 3
#define GREEN 5
#define RED 6

int speakerPin = 9;
int length = 15;
int pinSwitch = 8;
int pinSwitch2 = 7;
int time = 20000; // time interval of taking medicine
boolean oldSwitchState = LOW;
boolean newSwitchState = LOW;
boolean oldSwitch2State = LOW;
boolean newSwitch2State = LOW;
boolean buzzerState = LOW;
int record_time = 0;

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

//twinkle twinkle little star
char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc ";
int beats[] = {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4};
int tempo = 300;

void playTone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2)
  {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration)
{
  char names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
  int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};

  for (int i = 0; i < 8; i++)
  {
    if (names[i] == note)
    {
      playTone(tones[i], duration);
    }
  }
}

void switch_on()
{
  playNote('c', 150);
  playNote('e', 150);
  playNote('g', 150);
}

void switch_off()
{
  playNote('g', 150);
  playNote('e', 150);
  playNote('c', 150);
}

void song()
{
  for (int i = 0; i < length; i++)
  {
    if (notes[i] == ' ')
    {
      delay(beats[i] * tempo);
    }
    else
    {
      playNote(notes[i], beats[i] * tempo);
    }
    delay(tempo / 2);
  }
}

void reset()
{
  timeElapsed = record_time;
  yellow();
  delay(100);
  playNote('d', 500);
  blue();
  }

void setup()
{
  Serial.begin(9600);
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  yellow();
  pinMode(pinSwitch, INPUT);
  pinMode(pinSwitch2, INPUT);
}

void loop()
{

  int threshold = 100;
  long sensorValue = cs.capacitiveSensor(30);
  Serial.print(sensorValue);
  newSwitchState = digitalRead(pinSwitch);
  newSwitch2State = digitalRead(pinSwitch2);

  // sound switch
  if (newSwitchState != oldSwitchState)
  {
    if (newSwitchState == HIGH)
    {
      if (buzzerState == LOW)
      {
        buzzerState = HIGH;
        switch_on();
      }
      else
      {
        buzzerState = LOW;
        switch_off();
      }
    }
    oldSwitchState = newSwitchState;
  }

    // sensor
  if (sensorValue > threshold)
  {
    blue();
    record_time = timeElapsed;
    timeElapsed = 0;
    delay(1000);
  }

  // reset switch
  if (newSwitch2State != oldSwitch2State)
  {
    reset();
    oldSwitch2State = newSwitch2State;
  }

  if (timeElapsed > time) 
  {
    pink();
    if (timeElapsed < (time + 5) && buzzerState == HIGH)
    {
      song();
    }
  }

}
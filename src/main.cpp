#include <Arduino.h>
#include <CapacitiveSensor.h>
#include <elapsedMillis.h>

elapsedMillis timeElapsed;

CapacitiveSensor cs = CapacitiveSensor(4, 2);
const int buzzer = 9;

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

//

int speakerPin = 9;

int length = 15; // the number of notes

//twinkle twinkle little star
char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
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

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++)
  {
    if (names[i] == note)
    {
      playTone(tones[i], duration);
    }
  }
}

//

void song()
{
  for (int i = 0; i < length; i++)
  {
    if (notes[i] == ' ')
    {
      delay(beats[i] * tempo); // rest
    }
    else
    {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
  }
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
    if (timeElapsed < 12000)
    {
      song();
    }
    }
}
// Projeto 41 - Teremim ultrassônico

#define sensorPin 9

#define lowerFreq 123
#define upperFreq 2093
#define playHeight 36

float pwmRange, inch, cm, note;

void setup()
{
  pinMode(sensorPin, INPUT);
}

void loop()
{
  pwmRange = pulseIn(sensorPin, HIGH);

  inch = averageReading / 147;
  cm = inch * 2.54;

  // Mapeia o alcance de playHeight para as frequências mais altas e mais baixas
  note  = map(inch, 0, playHeight, lowerFreq, upperFreq);

  if (inch < playHeight)
  {
    tone(8, note);
  }
  else
  {
    noTone(8);
  }
}
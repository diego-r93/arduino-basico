// Projeto 10 - Mood lamp com controle serial

#include <string.h>

#define EOS     '\0'

char buffer[18];
unsigned red, green, blue;

byte RedPin = 11;
byte GreenPin = 10;
byte BluePin = 9;

void
setup()
{
  Serial.begin(9600);
  while(Serial.available())
    Serial.read();

  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
}

void 
loop()
{
  if (Serial.available() > 0)
  {
    byte index = 0;
    delay(100);
    int numChar = Serial.available();
    if (numChar > 15)
      numChar = 15;

    while (numChar--)
    {
      buffer[index++] = Serial.read();
    }
    splitString(buffer);
  }
}

void
splitString (char *data)
{
  Serial.print("Data entered: ");
  Serial.println(data);
  char *parameter;
  parameter = strtok(data, " ,");
  
  while (parameter != NULL)
  {
    setLED(parameter);
    parameter = strtok(NULL, " ,");
  }

  for (byte indice = 0; indice < 16; indice++)
    buffer[indice] = EOS;

  while (Serial.available())
    Serial.read();
}

void
setLED (char *data)
{
  char *validacao;
  int ANS;
  
  if ((data[0] == 'r') || (data[0] == 'R'))
  {
    ANS = (int) strtoul(data+1, &validacao, 10);
    ANS = constrain(ANS, 0, 255);
    analogWrite(RedPin, ANS);
    Serial.print("Red was set to: ");
    Serial.println(ANS);
  }

  if ((data[0] == 'g') || (data[0] == 'G'))
  {
    ANS = (int) strtoul(data+1, &validacao, 10);
    ANS = constrain(ANS, 0, 255);
    analogWrite(GreenPin, ANS);
    Serial.print("Green was set to: ");
    Serial.println(ANS);
  }

  if ((data[0] == 'b') || (data[0] == 'B'))
  {
    ANS = (int) strtoul(data+1, &validacao, 10);
    ANS = constrain(ANS, 0, 255);
    analogWrite(BluePin, ANS);
    Serial.print("Blue was set to: ");
    Serial.println(ANS);
  }
}

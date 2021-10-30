// Projeto 8 - Lâmpada de Humor

#include <stdlib.h>

float RGB1[3];
float RGB2[3];
float INC[3];

byte red, green, blue;

byte RedPin = 11;
byte GreenPin = 10;
byte BluePin = 9;

void 
setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  RGB1[0] = 0;
  RGB1[1] = 0;
  RGB1[2] = 0;

  RGB2[0] = random(256);
  RGB2[1] = random(256);
  RGB2[2] = random(256);
}

void
loop()
{
  randomSeed(analogRead(0));

  for (byte indice = 0; indice < 3; indice++)
  {
     INC[indice] = (RGB1[indice] - RGB2[indice])/256;
  }

  for (unsigned indice = 0; indice < 256; indice++)
  {
    red = (byte) (RGB1[0]);
    green = (byte) (RGB1[1]);
    blue = (byte) (RGB1[2]);

    analogWrite (RedPin, red);
    analogWrite (GreenPin, green);
    analogWrite (BluePin, blue);
    delay(100);

    RGB1[0] -= INC[0];
    RGB1[1] -= INC[1];
    RGB1[2] -= INC[2];
  }

  for (byte indice = 0; indice < 3; indice++)
  {
    RGB2[indice] = random(556) - 300;
    RGB2[indice] = constrain (RGB2[indice], 0 , 255);
    delay(100);
  }
}

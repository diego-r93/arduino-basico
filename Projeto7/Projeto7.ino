// Projeto 7 - Lâmpada pulsante

#include <math.h>

byte ledPin = 11;
float sinVal;
unsigned int ledVal;

void
setup()
{
  pinMode (ledPin, OUTPUT);
}

void
loop()
{
  for (int x = 0; x < 180; x++)      
  {
  sinVal = (sin(x * (M_PI/180)));   // converte graus para radianos e, então, obtém o valor do seno
  ledVal = (int) (sinVal * 255);
  analogWrite (ledPin, ledVal);
  delay (25);
  }
}

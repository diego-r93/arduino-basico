// Projeto 11 - Alarme com sonorizador piezo

#include <math.h>

#define  PIEZO_PIN       6

float sinVal;
unsigned int toneVal;

void
setup()
{
  pinMode (PIEZO_PIN, OUTPUT);
}

void
loop()
{
  for (int x = 0; x < 180; x++)      
  {
  sinVal = (sin(x * (M_PI/180)));   // converte graus para radianos e, então, obtém o valor do seno
  toneVal = 2000 + (int) (sinVal * 1000);
  tone(PIEZO_PIN, toneVal);
  delay (2);
  }
}

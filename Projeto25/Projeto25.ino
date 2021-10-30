// Projeto 25 - Controle de um servo

#include <Servo.h>

Servo servo1; // Cria um objeto servo

void setup()
{
  servo1.attach(5); // Anexa o servo no pino 5 ao objeto servo
}

void loop()
{
  int angle = analogRead(0);           // Lê o valor do potenciômetro
  angle = map(angle, 0, 1023, 0, 180); // Mapeia os valores de 0 a 180 graus
  servo1.write(angle);                 // escreve o ângulo para o servo
  delay(15);                           // Espera de 15ms para permitir que o servo atinja a posição
}

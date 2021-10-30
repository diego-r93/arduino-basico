// Projeto 27 - Controle de servos com joystick

#include <Servo.h>

Servo servo1; // Cria um objeto servo
Servo servo2; // Cria um segundo objeto servo
int pot1, pot2;

void setup()
{
  servo1.attach(5); // Anexa o servo, no pino 5, ao objeto servo1
  servo2.attach(6); // Anexa o servo, no pino 6, ao objeto servo2

  servo1.write(90); // Coloca o servo1 na posição inicial
  servo2.write(90); // Coloca o servo2 na posição inicial
}

void loop()
{
  pot1 = analogRead(3); // Lê o eixo x
  pot2 = analogRead(4); // Lê o eixo y
  pot1 = map(pot1, 0, 1023, 0, 180);
  pot2 = map(pot2, 0, 1023, 0, 180);
  servo1.write(pot1);
  servo2.write(pot2);
  delay(15);
}

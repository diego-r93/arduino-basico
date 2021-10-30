// Projeto 28 - Controle básico de um motor de passo

#include <Stepper.h>

// O valor de um passo é 360/ângulo de grau do motor

#define STEPS 200

// Cria um objeto stepper nos pinos 8, 9, 10, 11
Stepper stepper(STEPS, 8, 9, 10, 11);

void setup()
{
}

void loop()
{
  stepper.setSpeed(60);
  stepper.step(200);
  delay(100);
  stepper.setSpeed(20);
  stepper.step(-50);
  delay(100);
}

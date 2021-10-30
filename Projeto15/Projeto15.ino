// Projeto 15 - Controle de um motor simples

byte potPin = 0;        // pino analógico 0, conectado ao potenciômetro
int transistorPin = 11; // pino PWM 9 conectado à base do transistor
int potValue = 0;       // valor retornado do potenciômetro

void setup()
{
  pinMode(transistorPin, OUTPUT);
}

void loop()
{
  potValue = analogRead(potPin) / 4;    // lê o potenciômetro (entre 0 e 1024) e converte para um valor entre 0 e 255
  analogWrite(transistorPin, potValue); // controla o transistor por pwm (valores entre 0 e 255)
}

// Projeto 19 - Display de matriz de pontos LED - Animação básica

#include <TimerOne.h>

byte latchPin = 4;
byte clockPin = 6;
byte dataPin = 8;
byte led[8]; // array de bytes com 8 elementos para armazenar o sprite

void screenUpdate();

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  // carrega a representação binária da imagem estática no array
  led[0] = B11111111;
  led[1] = B10000001;
  led[2] = B10111101;
  led[3] = B10100101;
  led[4] = B10100101;
  led[5] = B10111101;
  led[6] = B10000001;
  led[7] = B11111111;
  // define um timer com duração de 10000 microssegundos
  Timer1.initialize(6000);              // anexa a função screenUpdate ao timer de interrupção
  Timer1.attachInterrupt(screenUpdate); // esse tempo de interrupção influencia na intensidade dos LEDs pois funciona como um PWM
}

void loop()
{
  // inverte cada linha da imagem binária, isso forma um quadrado dentro do outro
  // as linhas representam os catodos por isso devem ser zero para a corente fluir
  for (byte indice = 0; indice < 8; indice++)
    led[indice] = ~led[indice];
  delay(250); // tempo entre cada quadro
}

void screenUpdate()
{
  byte row = B10000000; // linha 1
  for (byte k = 0; k < 8; k++)
  {
    shiftOut(dataPin, clockPin, LSBFIRST, led[k]); // array do LED (invertido)
    shiftOut(dataPin, clockPin, LSBFIRST, ~row);   // linha do número binário

    // borda de subida para emitir dados
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    row >>= 1; // deslocamento para a direita (row = row >> 1)
  }

  // desliga todas as linhas até a próxima interrupção
  shiftOut(dataPin, clockPin, LSBFIRST, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, ~0);

  // borda de subida para emitir dados
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);
}

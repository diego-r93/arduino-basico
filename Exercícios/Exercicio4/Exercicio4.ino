// Exercício 4 - Contagem de 0 a 9

#include <TimerOne.h>

#define latchPin       4        // conectado ao pino 12 do 74HC595 (latch)
#define clockPin       6        // conectado ao pino 11 do 74HC595 (clock)
#define dataPin        8        // conectado ao pino 14 do 74HC595 (data)

byte frame = 0;                 // variável para armazenar o quadro atual sendo exibido

const byte led[10][8] = {
{
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B00111100
},{
  B00011000,
  B00111000,
  B01111000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00111100
},{
  B00111100,
  B01100110,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B01111110
},{
  B00111100,
  B01100110,
  B00000110,
  B00001100,
  B00001100,
  B00000110,
  B01100110,
  B00111100
},{
  B00001100,
  B00011100,
  B00101100,
  B01001110,
  B01111110,
  B01111100,
  B00001100,
  B00001100
},{
  B01111110,
  B01100000,
  B01100000,
  B01111100,
  B00000110,
  B00000110,
  B01100100,
  B00111000
},{
  B00111100,
  B01100010,
  B01100000,
  B01111100,
  B01100110,
  B01100110,
  B01100110,
  B00111100
},{
  B01111110,
  B00000110,
  B00001100,
  B00011000,
  B00110000,
  B00110000,
  B00110000,
  B00110000
},{
  B00111100,
  B01100110,
  B01100110,
  B00111100,
  B01100110,
  B01100110,
  B01100110,
  B00111100
},{
  B00111100,
  B01100110,
  B01100110,
  B00111110,
  B00000110,
  B00000110,
  B01100100,
  B00111100
}};


void
setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Timer1.initialize(6000);
  Timer1.attachInterrupt(screenUpdate);
}

void
loop() 
{
  frame++;                                                      // vai para o próximo quadro da animação
  if(frame > 9)                                                 // retorna ao frame 0 depois de passar pelo frame 7
    frame = 0;
  delay(1000);                                                  // taxa de atualizações (fps)
}

void
screenUpdate()
{
  byte row = B10000000;            // linha 1
  for (byte k = 0; k < 8; k++)
  {
    shiftOut(dataPin, clockPin, LSBFIRST, led[frame][k]);            // array do LED (invertido)
    shiftOut(dataPin, clockPin, LSBFIRST, ~row);                     // linha do número binário

    // borda de subida para emitir dados
    digitalWrite(latchPin, LOW);
    digitalWrite(latchPin, HIGH);
    row >>= 1;                          // deslocamento para a direita (row = row >> 1) 
  }

  // desliga todas as linhas até a próxima interrupção
  shiftOut(dataPin, clockPin, LSBFIRST, 0);
  shiftOut(dataPin, clockPin, LSBFIRST, ~0);
  
  // borda de subida para emitir dados
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH); 
}

// Projeto 20 - Display de matriz de pontos LED - Sprite com rolagem horizontal

#include <TimerOne.h>

#define latchPin       4        // conectado ao pino 12 do 74HC595 (latch)
#define clockPin       6        // conectado ao pino 11 do 74HC595 (clock)
#define dataPin        8        // conectado ao pino 14 do 74HC595 (data)

byte frame = 0;                 // variável para armazenar o quadro atual sendo exibido

byte led[8][8] = { {0,56,92,158,158,130,68,56},
                   {0,56,124,186,146,130,68,56},
                   {0,56,116,242,242,130,68,56},
                   {0,56,68,226,242,226,68,56},
                   {0,56,68,130,242,242,116,56},
                   {0,56,68,130,146,186,124,56},
                   {0,56,68,130,158,158,92,56},
                   {0,56,68,142,158,142,68,56} };

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
  for (byte i = 0; i < 8; i++)
    for (byte j = 0; j < 8; j++)
      led[i][j] = (led[i][j] << 1) | (led[i][j] >> 7);          // rotação bit a bit
      
  frame++;                                                      // vai para o próximo quadro da animação
  if(frame > 7)                                                 // retorna ao frame 0 depois de passar pelo frame 7
    frame = 0;
  delay(100);                                                   // taxa de atualizações (fps)
}

void
screenUpdate()
{
  byte row = B10000000;            // linha 1
  for (byte k = 0; k < 8; k++)
  {
    shiftOut(dataPin, clockPin, LSBFIRST, led[frame][k]);            // array do LED (invertido)
    shiftOut(dataPin, clockPin, LSBFIRST, ~row);              // linha do número binário

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

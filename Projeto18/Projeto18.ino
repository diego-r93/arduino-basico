// Projeto 18 - Contadores binários duplos de 8 bits

byte latchPin = 4;            // conectado ao pino 12 do 74HC595 (Latch)
byte clockPin = 6;            // conectado ao pino 11 do 74HC595 (Clock)
byte dataPin = 8;             // conectado ao pino 14 do 74HC595 (Data)

void 
setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void
loop()
{
  for (unsigned int indice = 0; indice < 256; indice++)
  {
    digitalWrite(latchPin, LOW);                              // define latchPin como LOW, depois como HIGH, para permitir o fluxo de dados
    shiftOut(dataPin, clockPin, LSBFIRST, indice);            // desloca os primeiros 8 bits
    shiftOut(dataPin, clockPin, LSBFIRST, 255 - indice);      // desloca o segundo conjunto de 8 bits
    digitalWrite(latchPin, HIGH);                             // transição LOW para HIGH
    delay(300);                                               // tempo de espera entre cada número 
  }
}

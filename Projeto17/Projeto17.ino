// Projeto 17 - Registrador de Deslocamento usado como contador de 8 bits

byte latchPin = 4; // conectado ao pino 12 do 74HC595 (Latch)
byte clockPin = 6; // conectado ao pino 11 do 74HC595 (Clock)
byte dataPin = 8;  // conectado ao pino 14 do 74HC595 (Data)

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop()
{
  for (unsigned int indice = 0; indice < 256; indice++)
  {
    digitalWrite(latchPin, LOW);  // define latchPin como LOW, depois como HIGH, para permitir o fluxo de dados
    shiftDataOut(indice);         // escreve o valor de indice
    digitalWrite(latchPin, HIGH); // transição LOW para HIGH
    delay(500);                   // tempo de espera entre cada número
  }
}

void shiftDataOut(unsigned int dataOut)
{
  // Desloca 8 bits, com o bit menos significativo (LSB) sendo deslocado primeiro
  // Sincronizado com a borda de subida do clock
  boolean pinState;

  for (byte indice = 0; indice < 8; indice++) // passa os bits em série para o 74HC595
  {
    digitalWrite(clockPin, LOW); // define clockPin como LOW antes de enviar o bit

    if (dataOut & (1 << indice)) // se o valor de dataOut e (AND) 1 (00000001), deslocado indice vezes para esquerda
      pinState = HIGH;           // for verdadeiro, defina pinState como HIGH, caso contrário defina como LOW
    else
      pinState = LOW;

    digitalWrite(dataPin, pinState); // envia o bit antes da borda de subida do clock
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(clockPin, LOW); // interrompe o deslocamento de dados
}

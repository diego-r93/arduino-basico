// Projeto 5 - Efeito de iluminação sequencial com LEDs

#define PINS        10

byte ledPin [PINS] = {4,5,6,7,8,9,10,11,12,13};  // cria um vetor para os pinos dos LEDS

unsigned int ledDelay = 65;                      // intervalo entre as alterações
short direction = 1;
char currentLED = 0;
unsigned long changeTime;

void 
setup()
{
  for (byte x = 0; x < 10; x++)
    pinMode (ledPin [x], OUTPUT);                 // define todos os pinos como saída

  changeTime = millis();
}

void 
loop()
{
  if ((millis() - changeTime) > ledDelay)        // verifica se já transcorreram ledDelay ms desde a última alteração
  {
    changeLED();
    changeTime = millis();
  }
}

void
changeLED()
{
  for (byte x = 0; x < 10; x++)                  // apaga todos os LEDs
    digitalWrite (ledPin [x], LOW);

  digitalWrite (ledPin [currentLED], HIGH);    // acende o LED atual
  currentLED += direction;                     // incrementa de acordo com o valor de direction

  if (currentLED == 9)                         // altera a direção se tivermos atingido o fim
    direction = -1;
  if (currentLED == 0)
    direction = 1;
}

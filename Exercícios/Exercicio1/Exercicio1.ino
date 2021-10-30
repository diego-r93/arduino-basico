// Efeitos com LEDs - Projeto 1

#define PINS 6

byte ledPin[PINS] = {5,6,7,8,9,10};   // vetor para os pinos dos LEDs

unsigned int ledDelay = 100;                   // intervalo entre as alterações
short direction = 1;
char currentLED[] = {0,9};                     // LEDs que estarão acesos
unsigned long changeTime;

void 
setup() 
{
  for (byte x = 0; x < 6; x++)
    pinMode (ledPin[x], OUTPUT);               // define todos os pinos como saídas

  changeTime = millis();
}

void 
loop() 
{
  if ((millis() - changeTime) > ledDelay)       // verifica se transcorreram ledDelay ms desde a última alteração
  {
    changeLED();
    changeTime = millis();
  }
}

void 
changeLED()
{
  for (byte x = 0; x < 6; x++)
    digitalWrite(ledPin[x], LOW);

  digitalWrite(ledPin[currentLED[0]], HIGH);      // acende os LEDs atuais
  digitalWrite(ledPin[currentLED[1]], HIGH);
  currentLED[0] += direction;
  currentLED[1] -= direction;                  // incremente os LEDS de acordo com o valor de direction

  if ((currentLED[0] == 6) || (currentLED[0] == 0))
    direction *= -1; 
}

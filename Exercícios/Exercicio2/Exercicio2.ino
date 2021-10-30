// Efeitos com LEDS - Projeto 2

#define PINS 10

byte ledPin[PINS] = {2,3,4,5,6,7,8,9,10,11};    // vetor para os pinos dos LEDs

unsigned int ledDelay = 100;                    // intervalo entre as alterações
short direction = -1;
byte currentLED = 9;
byte altura = 9;                        
unsigned long changeTime;

void 
setup() 
{
  for (byte x = 0; x < 10; x++)
    pinMode (ledPin[x], OUTPUT);               // define todos os pinos como saídas

  changeTime = millis();
}

void 
loop() 
{
  if ((millis() - changeTime) > ledDelay)      // verifica se transcorreram ledDelay ms desde a última alteração
  {
    changeLED();
    changeTime = millis();  
  }  
}

void
changeLED()
{
  for (byte x = 0; x < 10; x++)                // apaga todos os LEDs
    digitalWrite(ledPin[x], LOW);

  digitalWrite(ledPin[currentLED], HIGH);      // acende o LED atual
  currentLED += direction;

  if ((direction == 1) && (currentLED == altura))
    direction = -1;
  else
    if (currentLED == 0)
    {
      direction = 1;
      --altura;

      if (altura == 0)
      {
        altura = currentLED = 9;
        direction = -1;
      }  
    }
}  

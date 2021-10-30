// Projeto 3 - Police Lights

byte bluePin = 7;
byte redPin = 8;
unsigned int ledDelay = 50;               // 50 ms

void 
setup() 
{
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT); 
}

void 
loop() 
{
  for (int x = 0; x < 3; x++)
  {
    digitalWrite(bluePin, HIGH);
    delay(ledDelay);
    digitalWrite(bluePin, LOW);
    delay(ledDelay);
  }
  delay(100);

  for (int x = 0; x < 3; x++)
  {
    digitalWrite(redPin, HIGH);
    delay(ledDelay);
    digitalWrite(redPin, LOW);
    delay(ledDelay);
  }
  delay(100);
}

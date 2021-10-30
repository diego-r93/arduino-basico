// Projeto 14 - Sensor de luz

byte piezoPin = 8;
byte ledPin = 12;
byte ldrPin = 0;                      // LDR no pino analógico 0
int ldrValue = 0;                     // valor lido no LDR

void 
setup() 
{
  pinMode(ledPin, OUTPUT);
  for (byte x = 0; x < 3; x++)        // pisca o LED duas vezes para mostrar que o programa iniciou 
  {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }
  delay(1000);
  digitalWrite(ledPin, HIGH);
}

void
loop() 
{
  ldrValue = analogRead(ldrPin);      // lê o valor do LDR
  tone(piezoPin, 1000);               // toca um tom de 1000HZ no piezo
  delay(25);
  noTone(piezoPin);                  
  delay(ldrValue);
}

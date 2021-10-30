// Projeto 13 - Sensor de batida piezo

#define threshold    60

byte ledPin = 9;                      // led no pino digital 9
byte piezoPin = 5;                    // piezo no pino analógico 5
int sensorValue = 0;                  // armazena o valor lido do sensor
float ledValue = 0;                   // brilho do led

void 
setup() 
{
  pinMode(ledPin, OUTPUT);
  for (byte x = 0; x < 2; x++)
  {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(150);
  }
}

void 
loop() 
{
  sensorValue = analogRead(piezoPin);      // lê o valor do sensor

  if (sensorValue >= threshold)
    ledValue = 255;                        // se for detectadada uma batida o brilho do led será máximo

  analogWrite(ledPin, (int) ledValue);

  ledValue -= 0.05;                        // o led apaga lentamente

  if (ledValue <= 0)                       // impede de o valor de ledValue ser menor do que zero
    ledValue = 0;
}

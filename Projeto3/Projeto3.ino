// Projeto 3 - Semáforo

int redPin = 13;
int yellowPin = 12;
int greenPin = 11;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop()
{
  digitalWrite(greenPin, HIGH); // acende a luz verde
  delay(4500);                  // espera 4,5 segundos

  digitalWrite(yellowPin, HIGH); // acende a luz amarela
  digitalWrite(greenPin, LOW);   // apaga a luz verde
  delay(1500);                   // espera 1,5 segundos

  digitalWrite(redPin, HIGH);   // acende a luz vermelha
  digitalWrite(yellowPin, LOW); // apaga a luz amarela
  delay(6000);                  // espera 6 segundos

  digitalWrite(redPin, LOW); // apaga a luz vermelha
}

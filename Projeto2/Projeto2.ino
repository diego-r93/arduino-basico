// Projeto 2 - Sinalizador de código Morse S.O.S.

int ledPin = 10;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  // 3 pontos
  unsigned indice;
  for (indice = 0; indice < 3; indice++)
  {
    digitalWrite(ledPin, HIGH); // acende o LED
    delay(300);                 // espera 150 ms
    digitalWrite(ledPin, LOW);  // apaga o LED
    delay(200);                 // espera 100 ms
  }

  // espera 100 ms para marcar o intervalo entre as letras
  delay(200);

  // 3 traços
  for (indice = 0; indice < 3; indice++)
  {
    digitalWrite(ledPin, HIGH); // acende o LED
    delay(900);                 // espera 400 ms
    digitalWrite(ledPin, LOW);  // apaga o LED
    delay(200);                 // espera 100ms
  }

  // espera 100 ms para marcar o intervalo entre as letras
  delay(200);

  // 3 pontos novamente
  for (indice = 0; indice < 3; indice++)
  {
    digitalWrite(ledPin, HIGH); // acende o LED
    delay(300);                 // espera 150 ms
    digitalWrite(ledPin, LOW);  // apaga o LED
    delay(200);                 // espera 100 ms
  }

  // espera 5 segundos antes de repetir o sinal de S.O.S.
  delay(3000);
}

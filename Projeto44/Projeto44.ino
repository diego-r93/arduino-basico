// Projeto 44 - Leitor RFID simples

char val = 0; // Valor lido na porta serial

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    val = Serial.read(); // Lê a porta serial
    Serial.write(val);   // Imprime no monitor
  }
}
// Projeto 38 - Telêmetro ultrassônico simples

#define sensorPin 9
long pwmRange, inch, cm;

void setup()
{
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
}

void loop()
{
  pwmRange = pulseIn(sensorPin, HIGH);

  // 147 microssegundos por polegada, de acordo com o datasheet
  inch = pwmRange / 147;

  // Converte polegadas em centímetros
  cm = inch * 2.54;

  Serial.print(inch);
  Serial.print(" inches   ");
  Serial.print(cm);
  Serial.println(" cm");
}
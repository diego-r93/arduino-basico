// Projeto 24 - Display LCD de temperatura

#include <LiquidCrystal.h>

// Inicializa a biblioteca com os números dos pinos de interface

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Cria um objeto lcd e atribui os pinos

int maxC = 0, minC = 100, maxF = 0, minF = 212;
const int buttonPin = 8;

void setup()
{
  lcd.begin(16, 2); // Define o display com 16 colunas e 2 linhas
  analogReference(INTERNAL);
  // analogReference(INTERNAL1V1); // Para Arduino Mega
  pinMode(buttonPin, INPUT);
  lcd.clear();
  Serial.begin(9600);
}

void loop()
{
  lcd.setCursor(0, 0);         // Define o cursor a posição de início
  int sensor = analogRead(A0); // Lê a temperatura do sensor
  Serial.println(sensor);
  boolean buttonState = digitalRead(buttonPin);

  switch (buttonState) // Decide por escala em Celsius ou Fahrenheit
  {
  case HIGH:
    celsius(sensor);
    break;
  case LOW:
    fahrenheit(sensor);
  }
  delay(500);
}

void celsius(int sensor)
{
  lcd.setCursor(0, 0);
  int temp = sensor * 0.1074188; // Converte em Celsius
  lcd.print(temp);
  lcd.write(B11011111); // Símbolo do grau
  lcd.print("C ");

  if (temp > maxC)
    maxC = temp;
  if (temp < minC)
    minC = temp;

  lcd.setCursor(0, 1);
  lcd.print("H=");
  lcd.print(maxC);
  lcd.write(B11011111);
  lcd.print("C L=");
  lcd.print(minC);
  lcd.write(B11011111);
  lcd.print("C ");
}

void fahrenheit(int sensor)
{
  lcd.setCursor(0, 0);
  float temp = ((sensor * 0.1074188) * 1.8) + 32; // Converte em Fahrenheit
  lcd.print((int)temp);
  lcd.write(B11011111); // Símbolo do grau
  lcd.print("F ");

  if (temp > maxF)
    maxF = temp;
  if (temp < minF)
    minF = temp;

  lcd.setCursor(0, 1);
  lcd.print("H=");
  lcd.print(maxF);
  lcd.write(B11011111);
  lcd.print("F L=");
  lcd.print(minF);
  lcd.write(B11011111);
  lcd.print("F ");
}

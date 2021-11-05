// Projeto 39 - Display ultrassônico de distância

#include "LedControl.h"

#define sensorPin 9
#define switchPin 7
#define DataIn 2
#define CLK 4
#define LOAD 3
#define NumChips 1
#define samples 5.0

float pwmRange, averageReading, inch, cm;
LedControl lc = LedControl(DataIn, CLK, LOAD, NumChips);

void setup()
{
  // inicializa o MAX7219
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  pinMode(sensorPin, INPUT);
  pinMode(switchPin, INPUT);
}

void loop()
{
  averageReading = 0;
  inch = averageReading / 147;
  cm = inch * 2.54;

  if (digitalRead(switchPin))
  {
    displayDigit(inch);
  }
  else
  {
    displayDigit(cm);
  }
}

void displayDigit(float value)
{
  int number = value * 100;
  lc.setDigit(0, 4, number / 10000, false);           // dígito das centenas
  lc.setDigit(0, 3, (number % 10000) / 1000, false);  // dígito das dezenas
  lc.setDigit(0, 2, (number % 1000) / 100, true);     // primero dígito com DP ligado
  lc.setDigit(0, 1, (number % 100) / 10, false);      // dígito dos décimos
  lc.setDigit(0, 0, number % 10, false);              // dígito dos centésimos
}
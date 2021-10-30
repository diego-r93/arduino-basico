// Projeto 34 - Tela de toque com teclado

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define LEFT 8   // Esquerda (X1) para o pino digital 8
#define BOTTOM 9 // Base (Y2) para o pino digital 9
#define RIGHT 10 // Direita (X2) para opino digital 10
#define TOP 11   // Topo (Y1) para o pino digital 11

// Conexões analógicas
#define TOP_INPUT 0   // Topo (Y1) para o pino analógico 0
#define RIGHT_INPUT 1 // Direita (X2) para o pino analógico 1

int coordX = 0, coordY = 0;
char buffer[20];

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  if (touch())
  {
    if ((coordX > 220 && coordX < 360) && (coordY > 160 && coordY < 340))
    {
      lcd.print("1");
    }
    if ((coordX > 220 && coordX < 360) && (coordY > 410 && coordY < 590))
    {
      lcd.print("2");
    }
    if ((coordX > 220 && coordX < 360) && (coordY > 670 && coordY < 850))
    {
      lcd.print("3");
    }
    if ((coordX > 390 && coordX < 530) && (coordY > 170 && coordY < 330))
    {
      lcd.print("4");
    }
    if ((coordX > 390 && coordX < 530) && (coordY > 410 && coordY < 590))
    {
      lcd.print("5");
    }
    if ((coordX > 390 && coordX < 530) && (coordY > 670 && coordY < 850))
    {
      lcd.print("6");
    }
    if ((coordX > 570 && coordX < 710) && (coordY > 160 && coordY < 340))
    {
      lcd.print("7");
    }
    if ((coordX > 570 && coordX < 710) && (coordY > 410 && coordY < 590))
    {
      lcd.print("8");
    }
    if ((coordX > 570 && coordX < 710) && (coordY > 670 && coordY < 850))
    {
      lcd.print("9");
    }
    if ((coordX > 750 && coordX < 890) && (coordY > 410 && coordY < 590))
    {
      lcd.print("0");
    }
    if ((coordX > 750 && coordX < 890) && (coordY > 160 && coordY < 340))
    {
      scrollLCD();
    }
    if ((coordX > 750 && coordX < 890) && (coordY > 680 && coordY < 850))
    {
      lcd.clear();
    }
  }

  delay(250);
}

// Retorna TRUE se tocada e define as coordenadas touchX e touchY
boolean touch()
{
  boolean touch = false;

  // Pega as coordenadas horizontais
  pinMode(TOP, INPUT); // Topo e base com impedância alta
  pinMode(BOTTOM, INPUT);

  pinMode(LEFT, OUTPUT);
  digitalWrite(LEFT, LOW); // Define o lado esquerdo para o terra
  pinMode(RIGHT, OUTPUT);  // Define o lado direito para os +5V
  digitalWrite(RIGHT, HIGH);

  delay(3);
  coordX = analogRead(TOP_INPUT);

  // Pega as coordenadas verticais
  pinMode(RIGHT, INPUT); // Esquerda e direita com impedância alta
  pinMode(LEFT, INPUT);

  pinMode(BOTTOM, OUTPUT); // Define a base para o terra
  digitalWrite(BOTTOM, LOW);

  pinMode(TOP, OUTPUT); // Define o topo para os +5V
  digitalWrite(TOP, HIGH);

  delay(3);
  coordY = analogRead(RIGHT_INPUT);

  // Se as coordenadas lidas forem menores do que 1000 e maiores do que 24
  // Significa que a tela foi tocada
  if (coordX < 1000 && coordX > 24 && coordY < 1000 && coordY > 24)
  {
    touch = true;
  }

  return touch;
}

void scrollLCD()
{
  for (int scrollNum = 0; scrollNum < 20; scrollNum++)
  {
    lcd.scrollDisplayLeft();
    delay(100);
  }
  lcd.clear();
}
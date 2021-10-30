// Projeto 35 - Controlador de luz com tela de toque

#define LEFT 8   // Esquerda (X1) para o pino digital 8
#define BOTTOM 9 // Base (Y2) para o pino digital 9
#define RIGHT 10 // Direita (X2) para opino digital 10
#define TOP 11   // Topo (Y1) para o pino digital 11

// Conexões analógicas
#define TOP_INPUT 0   // Topo (Y1) para o pino analógico 0
#define RIGHT_INPUT 1 // Direita (X2) para o pino analógico 1

// Pinos RGB
#define PIN_R 3
#define PIN_G 5
#define PIN_B 6

int coordX = 0, coordY = 0;
boolean ledState = true;
int red = 100, green = 100, blue = 100;

void setup()
{
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
}

void loop()
{
  if (touch())
  {
    if ((coordX > 200 && coordX < 360) && (coordY > 510 && coordY < 800))
    {
      ledState = true;
      delay(50);
    }
    if ((coordX > 200 && coordX < 360) && (coordY > 170 && coordY < 480))
    {
      ledState = false;
      delay(50);
    }
    if ((coordX > 400 && coordX < 950) && (coordY > 580 && coordY < 770))
    {
      coordX = constrain(coordX, 420, 930);
      red = map(coordX, 420, 930, 0, 255);
    }
    if ((coordX > 400 && coordX < 950) && (coordY > 370 && coordY < 560))
    {
      coordX = constrain(coordX, 420, 930);
      green = map(coordX, 420, 930, 0, 255);
    }
    if ((coordX > 400 && coordX < 950) && (coordY > 160 && coordY < 340))
    {
      coordX = constrain(coordX, 420, 930);
      blue = map(coordX, 420, 930, 0, 255);
    }

    delay(10);
  }

  if (ledState)
  {
    analogWrite(PIN_R, red);
    analogWrite(PIN_G, green);
    analogWrite(PIN_B, blue);
  }
  else
  {
    analogWrite(PIN_R, 0);
    analogWrite(PIN_G, 0);
    analogWrite(PIN_B, 0);
  }
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
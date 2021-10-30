// Projeto 33 - Tela de toque básica

#define LEFT 8   // Esquerda (X1) para o pino digital 8
#define BOTTOM 9 // Base (Y2) para o pino digital 9
#define RIGHT 10 // Direita (X2) para opino digital 10
#define TOP 11   // Topo (Y1) para o pino digital 11

// Conexões analógicas
#define TOP_INPUT 0   // Topo (Y1) para o pino analógico 0
#define RIGHT_INPUT 1 // Direita (X2) para o pino analógico 1

int coordX = 0, coordY = 0;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (touch()) // Se a tela foi tocada, imprime as coordenadas
  {
    Serial.print(coordX);
    Serial.print(" ");
    Serial.println(coordY);
    delay(250);
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
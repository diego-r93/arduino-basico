// Projeto 22 - Display de matriz de pontos LED - Pong Game

#include <LedControl.h>

#define POT_PIN 5 // Pino do Potenciômetro

LedControl myMatrix = LedControl(2, 4, 3, 1); // Cria uma instância de uma matriz

int column = 0, row = random(8);
int directionX = 1, directionY = 1;
int potVal;
int movement_interval = 300;
int counter = 0;

void setup()
{
  myMatrix.shutdown(0, false); // Modo de desligamento desligado
  myMatrix.setIntensity(0, 8); // Define o brilho como médio
  randomSeed(analogRead(0));   // Lê um valor aleatório no pino A0 e usa como "semente"
  oops();
}

void loop()
{
  potVal = analogRead(POT_PIN);        // Guarda o valor do potenciômetro
  potVal = map(potVal, 0, 1024, 0, 6); // Mapeia o valor lido entre 0 e 6;

  if (column == 6 && (potVal == row || potVal + 1 == row || potVal + 2 == row)) // Caso a bola esteja na coluna 6 e coincida com a raquete
    directionX = -1;                                                            // O sentido de movimento no eixo x se inverte
  if (column == 0)                                                              // Se a bola chegar na coluna 0
    directionX = 1;                                                             // O sentido de movimento no eixo x se inverte
  if (row == 7)                                                                 // Se a bola chegar na linha 7
    directionY = -1;                                                            // O sentido de movimento no eixo y se inverte
  if (row == 0)                                                                 // Se a bola chegar na linha 0
    directionY = 1;                                                             // O sentido de movimento no eixo y se inverte
  if (column == 7)                                                              // Se a bola ultrapassar a raquete
    oops();                                                                     // A função oops é chamada para piscar os LEDS e reiniciar os valores

  column += directionX; // As coordenadas das linhas e colunas são acrescidas
  row += directionY;    // pelos valores em directionX e directionY
  displayDashAndDot();  // Função que exibe a raquete
}

void oops()
{
  for (byte x = 0; x < 3; x++) // Acende todas as linhas e colunas piscando 3 vezes
  {
    myMatrix.clearDisplay(0);
    delay(250);

    for (byte y = 0; y < 8; y++)
    {
      myMatrix.setRow(0, y, 255);
    }
    delay(250);
  }

  counter = 0; // Reinicia o display (default)
  movement_interval = 300;
  column = 0;
  row = random(8);
  displayDashAndDot();
}

void displayDashAndDot()
{
  myMatrix.clearDisplay(0);              // Apaga o display
  myMatrix.setLed(0, column, row, HIGH); // Acende a posição da bola
  myMatrix.setLed(0, 7, potVal, HIGH);   // Acende a posição da raquete
  myMatrix.setLed(0, 7, potVal + 1, HIGH);
  myMatrix.setLed(0, 7, potVal + 2, HIGH);

  if (!(counter % 10)) // Diminui o intervalo de tempo em 5s à cada 10s
    movement_interval -= 5;

  delay(movement_interval);
  counter++;
}

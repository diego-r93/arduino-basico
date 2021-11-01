// Projeto 32 - Barógrafo digital

#include <glcd.h>
#include "Fonts/allFonts.h"

#include <Wire.h> // Para utilizar a comunicação I2C

// É necessário saber a altitude na sua localização para calcular a pressão ao nível
// médio do mar
#define MYALTITUDE

#define MY_ALTITUDE 13 // Altitude ao nivel do mar para minha localização (obtida pelo Google Earth)

// Endereços dos Registradores

#define SENSOR_ADRESS 0x60        // Endereço do MPL3115A1 lido no datasheet
#define SENSOR_CONTROL_REG_1 0x26 // Endereço do registrador de controle
#define SENSOR_DR_STATUS 0x00     // Endereço do registrador de status DataReady
#define SENSOR_OUT_P_MSB 0x01     // Endereço inicial de registradores Pressure Data

// Intervalo de tempo em segundos (aproximado) por tique do gráfico
// escala para deduzir da leitura hPa para ajustar dentro do intervalo 990-1030 de 40 pixels
#define INTERVAL 900

float baroAltitudeCorrectionFactor = 1 / (pow(1 - MY_ALTITUDE / 44330.77, 5.255877));

byte I2Cdata[5] = {0, 0, 0, 0, 0}; // Buffer para o sensor

float temperature, pressure, baroPressure, buffer[30];
int dots[124], dotCursor = 0, counter = 0, index = 0, numReadingsBuffered = 0;

void setup()
{
  Wire.begin();       // Conecta o barramento I2C  

  I2C_Write(SENSOR_CONTROL_REG_1, 0b00000000); // Coloca em Standby
                                               // Só é possível alterar os bits do registrador no modo Standby
  I2C_Write(SENSOR_CONTROL_REG_1, 0b00111000); // Define oversampling como 128

  GLCD.Init();                        // Inicializa a biblioteca
  GLCD.ClearScreen();
  GLCD.SelectFont(System5x7, BLACK);  // Carrega a fonte
  GLCD.DrawRect(1, 1, 125, 44);       // Desenha um retângulo

  for (int x = 0; x < 128; x+=5)  // Desenha a escala vertical
  {
    GLCD.SetDot(0,1 + x, BLACK);
    GLCD.SetDot(127, 1+ x, BLACK);
  }

  for (int x = 0; x < 128; x +=5) // Desenha a escala horizontal
  {
    GLCD.SetDot(1 + x, 0, BLACK);
  }

  // Limpa o array para o nível do mar padrão
  for (byte x = 0; x < 124; x++)
  {
    dots[x] = 1013;
  }

  Read_Sensor_Data();
  drawPoints(dotCursor);
}

void loop()
{
  ReadSensorData();

  GLCD.CursorToXY(0, 49); // Imprime a pressão
  GLCD.print("hPa:");
  GLCD.CursorToXY(24, 49);
  GLCD.print(baroPressure/100);
  GLCD.print("  "); // Apaga qualquer valor antigo mais longo do que o valor novo

  float tempF = (temperature * 1.8) + 32;

  GLCD.cursorToXY(0, 57); // Imprime a temperatura
  GLCD.print("Temp:");
  GLCD.cursorToXY(28, 57);
  // LCD.print(temperature);
  // Altera a temperatura para Celsius
  LCD.print(tempF);
  GLCD.print("  "); // Apaga qualquer valor antigo mais longo do que o valor novo

  delay(1000);

  GLCD.CursorToXY(84, 49);  // Imprime a tendência
  LCD.print("TREND:");
  GLCD.CursorToXY(84, 57);
  printTrend();

  counter++;
  if (counter == INTERVAL)
  {
    drawPoints(dotCursor);
    counter = 0;
  }
}

void drawPoints(int position)
{
  dots[dotCursor] = (int) baroPressure/100;
  int midscale = dots[dotCursor];       // Centraliza a escala do gráfico na leitura atual
  GLC.FillRect(2, 2, 123, 40, WHITE);   // Limpa a área do gráfico

  for (int x = 0; x < 124; x++)
  {
    // Limita a região do gráfico
    int y = constrain(22 - ((dots[position] - midscale)), 0, 44);
    GLCD.SetDot(125 - x, y, BLACK);
    position--;
    if (position < 0)
    {
      position = 123;
    }
  }
  dotCursor++;
  if (dotCursor > 123)
  {
    dotCursor = 0;
  }
}

// Calcula a tendência desde o último ponto de dados e imprime
void printTrend()
{
  int dotCursor2 = dotCursor - 1;

  if (dotCursor2 < 0)
    dotCursor2 = 123;
  
  int val1 = dots[dotCursor2];
  int dotCursor3 = dotCursor2 - 1;

  if (dotCursor3 < 0)
    dotCursor3 = 123;
  
  int val2 = dots[dotCursor3];

  if (val1 > val 2)
    GLCD.print("RISING ");

  if (val1 == val 2)
    GLCD.print("STEADY ");

  if (val1 < val 2)
    GLCD.print("FALING ");
}

// Função para fazer a leitura de pressão e temperatura
void ReadSensorData()
{
  float tempPressure;

  I2C_Write(SENSOR_CONTROL_REG_1, 0b00111010); // bit 1 em modo one-shot
                                               // Espera que a medição esteja completa
                                               // bit One-shot vai limpar quando estiver concluído
                                               // Lê o registrador de corrente (controle do sensor)
                                               // Repete até que o sensor limpe o bit OST
  do
  {
    Wire.requestFrom(SENSOR_ADRESS, 1);
  } while ((Wire.read() & 0b00000010) != 0);

  I2C_ReadData(); // Lê os registradores do sensor

  temperature = calcTemperature();
  pressure = calcPressure();
  buffer[index++] = tempPressure;

  if (index > 29) index = 0;    // Ao final do buffer, retorne ao início

  numReadingsBuffered++;

  if(numReadingsBuffered > 30) numReadingsBuffered = 30;

  float mean = 0;
  for (int i = 0; i < numReadingsBuffered; i++)
  {
    mean = mean + buffer[i];
  }
  pressure = mean/numReadingsBuffered;
  baroPressure = pressure * baroAltitudeCorrectionFactor;
}

float calcPressure()
{
  unsigned long mPressure = I2Cdata[0];
  unsigned long cPressure = I2Cdata[1];
  float lPressure = (float)(I2Cdata[2] >> 4) / 4;
  return ((float)(mPressure << 10 | cPressure << 2) + lPressure);
}

// Essa função reúne a leitura da temperatura dos valores no buffer de entrada
float calcTemperature()
{
  int mTemp;
  float lTemp;

  mTemp = I2Cdata[3];                      // Temperatura em graus celsius inteiros
  lTemp = (float)(I2Cdata[4] >> 4) / 16.0; //Porção fracionária da temperatura
  return ((float)(mTemp + lTemp));
}

void I2C_ReadData()
{
  byte readUnsuccessful;

  do
  {
    byte i = 0;
    byte dataStatus = 0;

    Wire.beginTransmission(SENSOR_ADRESS);
    Wire.write(SENSOR_OUT_P_MSB);
    Wire.endTransmission(false);

    // Lê 5 bytes. 3 para pressão, 2 para temperatura

    Wire.requestFrom(SENSOR_ADRESS, 5);
    while (Wire.available())
      I2Cdata[i++] = Wire.read();

    /* Em alguns modos é possível que o sensor atualize a leitura da pressão enquanto estamos
    * no meio do processo de sua leitura, neste caso a nossa cópia não serve para nada
    * (partes de duas leituras distintas). Podemos checar os bits no registrador DR (data ready) 
    * para verificar se isso aconteceu
    */

    Wire.beginTransmission(SENSOR_ADRESS);
    Wire.write(SENSOR_DR_STATUS);
    Wire.endTransmission(false);

    // Lê 5 bytes. 3 para pressão, 2 para temperatura
    Wire.requestFrom(SENSOR_ADRESS, 1);
    dataStatus = Wire.read();
    readUnsuccessful = (dataStatus & 0x60) != 0;

    /* Este processo não será bem sucedido se dados doram sobrescritos enquanto realizávamos a 
    * leitura dos dados de pressão ou de temperatura.
    * Neste caso, continua-se realizando a leitura até que se obtenha uma leitura limpa e 
    * bem-sucedida.
    */
  } while (readUnsuccessful);
}

// Essa função escreve um byte no I2C
void I2C_Write(byte regAddr, byte value)
{
  Wire.beginTransmission(SENSOR_ADRESS);
  Wire.write(regAddr);
  Wire.write(value);
  Wire.endTransmission(true);
}
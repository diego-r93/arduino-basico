// Projeto 31 - Sensor digital de pressão

#include <Wire.h> // Para utilizar a comunicação I2C

#define MY_ALTITUDE 13 // Altitude ao nivel do mar para minha localização (obtida pelo Google Earth)

// Endereços dos Registradores

#define SENSOR_ADRESS 0x60        // Endereço do MPL3115A1 lido no datasheet
#define SENSOR_CONTROL_REG_1 0x26 // Endereço do registrador de controle
#define SENSOR_DR_STATUS 0x00     // Endereço do registrador de status DataReady
#define SENSOR_OUT_P_MSB 0x01     // Endereço inicial de registradores Pressure Data

float baroAltitudeCorrectionFactor = 1 / (pow(1 - MY_ALTITUDE / 44330.77, 5.255877));

byte I2Cdata[5] = {0, 0, 0, 0, 0}; // Buffer para o sensor

void setup()
{
  Wire.begin();       // Conecta o barramento I2C
  Serial.begin(9600); // Inicia as comunicações Seriais
  Serial.println("Setup");
  I2C_Write(SENSOR_CONTROL_REG_1, 0b00000000); // Coloca em Standby
                                               // Só é possível alterar os bits do registrador no modo Standby
  I2C_Write(SENSOR_CONTROL_REG_1, 0b00111000); // Define oversampling como 128
  Serial.println("Done.");
}

void loop()
{
  float temperature, pressure, baroPressure;

  ReadSensorData();
  temperature = calcTemperature();
  pressure = calcPressure();
  baroPressure = pressure * baroAltitudeCorrectionFactor;
  Serial.print("Absolute pressure: ");
  Serial.print(pressure);
  Serial.print(" Pa,    Barometer: ");
  Serial.print(baroPressure);
  Serial.print(" Pa,    Temperature: ");
  Serial.print(temperature);
  Serial.print(" C\n");
  delay(1000);
}

// Função para fazer a leitura de pressão e temperatura

void ReadSensorData()
{
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
}

// Essa função reúne a leitura da pressão dos valores no buffer de leitura
// Os dois bits menos significativos são fracionários, então divida por 4

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

// Essa função lê dados do barômetro e de temperatura (5 bytes)

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

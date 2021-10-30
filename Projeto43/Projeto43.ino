// Projeto 43 - Registrador de dados de temperatura em um cartão SD

#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DS1307.h>

#define ONE_WIRE_BUS 3 // Linha de dados vai para o pino digital 3
#define TEMPERATURE_PRECISION 12

File File1;

OneWire oneWire(ONE_WIRE_BUS); // Prepara uma instância de OneWire

DallasTemperature sensors(&oneWire); // Passa a instância oneWire para Dallas Temperature

// arrays para armazenar os endereços dos dispositivos
DeviceAddress insideThermometer = {0x28, 0xAA, 0x01, 0xF8, 0x41, 0x14, 0x01, 0x3E};
DeviceAddress outsideThermometer = {0x28, 0xAA, 0xC5, 0x30, 0x3E, 0x14, 0x01, 0x96};

float tempC, tempF;

DS1307 rtc(4, 5); // Inicializa o DS1307

void setup()
{
  Serial.println("Initializing the SD Card...");

  if (!SD.begin())
  {
    Serial.println("Initialization Failed!");
    return;
  }
  Serial.println("Initialization Complete.\n");

  rtc.halt(false); // Define o clock para o modo de execução

  Serial.begin(9600);
  Serial.println("Type any character to start");
  while (!Serial.available())
  {
  };

  Serial.println();

  // Inicializa os sensores da biblioteca
  sensors.begin();
  Serial.println("Initialising Sensors.\n");

  // Define a resolução
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
  delay(100);

  // Define o tempo no RCT
  //rtc.setDOW(DIA_DA_SEMANA);
  //rtc.setTime();
  //rtc.setDate();
}

void loop()
{
  File1 = SD.open("TEMPLOG.txt", FILE_WRITE);
  Serial.println("File Opened.");

  if (File1)
  {
    File1.print(rtc.getDateStr());
    Serial.print(rtc.getDateStr());
    File1.print(", ");
    Serial.print(", ");
    File1.print(": Inside: ");
    Serial.print(": Inside: ");
    getTemperature(insideThermometer);
    File1.print(tempC);
    Serial.print(tempC);
    File1.print("C Outside: ");
    Serial.print("C Outside: ");
    getTemperature(outsideThermometer);
    File1.print(tempC);
    Serial.print(tempC);
    File1.println(" C");
    Serial.println(" C");
    Serial.println("Data written to file.");
  }

  File1.close();
  Serial.println("File Closed.\n");
  Serial.println("Safe to disconnect card");
  delay(10000);
  Serial.println("Card in use, do not disconnect!!");
}

void getTemperature(DeviceAddress deviceAddress)
{
  sensors.requestTemperatures();
  tempC = sensors.getTempC(deviceAddress);
  tempF = DallasTemperature::toFahrenheit(tempC);
}

// Projeto 37 - Parte 2

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS            3              // Linha de dados vai para o pino digital 3
#define TEMPERATURE_PRECISION  12

OneWire oneWire(ONE_WIRE_BUS);                 // Prepara uma instância de OneWire 

DallasTemperature sensors(&oneWire);           // Passa a instância oneWire para Dallas Temperature


// arrays para armazenar os endereços dos dispositivos
DeviceAddress insideThermometer =  { 0x28, 0xAA, 0x01, 0xF8, 0x41, 0x14, 0x01, 0x3E };
DeviceAddress outsideThermometer = { 0x28, 0xAA, 0xC5, 0x30, 0x3E, 0x14, 0x01, 0x96 };


void setup()
{
  sensors.begin();              // Inicia a biblioteca
  Serial.begin(9600);
  Serial.println("Initializing...");
  Serial.println();

  // Define a resolução
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
}

void loop()
{
  sensors.requestTemperatures();
  delay(750);
  Serial.print("Inside Temp: ");
  printTemperature(insideThermometer);
  Serial.println();
  Serial.print("Outside Temp: ");
  printTemperature(outsideThermometer);
  Serial.println();
  delay(3000);
}


// Função para imprimir a temperatura de um dispositivo
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}  
  

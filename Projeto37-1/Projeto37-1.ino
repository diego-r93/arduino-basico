// Projeto 37 - Parte 1

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS       3              // Linha de dados vai para o pino digital 3

OneWire oneWire(ONE_WIRE_BUS);            // Prepara uma instância de OneWire 

DallasTemperature sensors(&oneWire);      // Passa a instância oneWire para Dallas Temperature


// Varriável para armazenar os endereços dos dispositivos
DeviceAddress Thermometer;

int deviceCount = 0;


void setup()
{
  sensors.begin();              // Inicia a biblioteca
  Serial.begin(9600);
  
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");

  for (byte i = 0; i < deviceCount; i++)
  {
    if (!sensors.getAddress(Thermometer, i))
    {
      Serial.print("Unable to find address for Device ");
      Serial.println(i+1);
    }
  }

  // Imprime os endereços dos dispositivos
  Serial.println("Printing Addresses...\n");

  for (byte i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    sensors.getAddress(Thermometer, i);
    printHexAddress(Thermometer);
  }
}


void loop(void)
{
  /*  Chama sensors.requestTemperatures() para emitir uma solicitação 
   *  de temperatura global a todos os dispositivos do barramento.
   */
   
  Serial.print("\nRequesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
  delay(750);

  // Imprime as informações do dispositivo
  for (byte i = 0; i < deviceCount; i++)
  {
    sensors.getAddress(Thermometer, i);
    printData(Thermometer);
    Serial.print("");
    delay(1000);
  }
}


// Função para imprimir o endereço de um dispositivo 
void printAddress(DeviceAddress deviceAddress)
{ 
  for (byte i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 0x10)     // < 16 
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}


// Função para imprimir o endereço de um dispositivo em formato Hexadecimal com 0x
void printHexAddress(DeviceAddress deviceAddress)
{ 
  for (byte i = 0; i < 8; i++)
  {
    Serial.print("0x");
    if (deviceAddress[i] < 0x10)     // < 16 
      Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
    if (i < 7) Serial.print(", ");
  }
  Serial.println("");
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

// Função para imprimir as informações do dispositivo
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

// Projeto 48 - Sistema de alerta por email

#include <Ethernet.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define EMAIL_INTERVAL 300
#define HIGH_THRESHOLD 40
#define LOW_THRESHOLD 10

// Fio de dados é plugado ao pino 3 do Arduino
#define ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION 12

const unsigned time = 1000;
float tempC, tempF;
char message1[35], message2[35];
char subject[] = "ARDUINO: TEMPERATURE ALERT!\0";
unsigned long lastMessage = 0;

// Prepara uma instância de OneWire (chamada OneWire) para se comunicar com qualquer
// dispositivo OneWire (não apenas com CIs de temperatura Maxim/Dallas)
OneWire oneWire(ONE_WIRE_BUS);

// Passa o endereço da instância oneWire ao Dallas Temperature
DallasTemperature sensors(&oneWire);

// Arrays para armazenar os endereços dos dispositivos
DeviceAddress insideThermometer = {0x28, 0xAA, 0xC5, 0x30, 0x3E, 0x14, 0x01, 0x96};

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {192, 168, 1, 175};
byte server[] = {200, 147, 99, 132}; // Endereço do servidor de e-mail

EthernetClient client;

void sendEmail(char subject[], char message1[], char message2[], float temp)
{
  Serial.println("connecting...");
  if (client.connect(server, 587))
  {
    Serial.println("connected");
    client.println("EHLO MYSERVER");
    checkEmail();
    delay(time);
    client.println("AUTH LOGIN");
    checkEmail();
    delay(time);
    client.println("ZGllZ28tYXJkdWlub0Bib2wuY29tLmJy");
    checkEmail();
    delay(time);
    client.println("aXp1czM5OTE=");
    checkEmail();
    delay(time);
    client.println("MAIL FROM: <diego-arduino@bol.com.br>");
    checkEmail();
    delay(time);
    client.println("RCPT TO: <diegorodrigues-5@hotmail.com>");
    checkEmail();
    delay(time);
    client.println("DATA");
    checkEmail();
    delay(time);
    client.println("From: <diego-arduino@bol.com.br>");
    checkEmail();
    delay(time);
    client.println("To: <diegorodrigues-5@hotmail.com>");
    checkEmail();
    client.print("SUBJECT: ");
    client.println(subject);
    checkEmail();
    delay(time);
    client.println();
    delay(time);
    client.println(message1);
    checkEmail();
    delay(time);
    client.println(message2);
    checkEmail();
    delay(time);
    client.print("Temperature: ");
    client.println(temp);
    checkEmail();
    delay(time);
    client.println(".");
    checkEmail();
    delay(time);
    client.println("QUIT");
    checkEmail();
    delay(time);
    Serial.println("Email sent.");
    lastMessage = millis();
  }
  else
  {
    Serial.println("Connection failed");
  }
}

void checkEmail()
{
  while (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected())
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
}

void getTemperature(DeviceAddress deviceAddress)
{
  tempC = sensors.getTempC(deviceAddress);
  tempF = DallasTemperature::toFahrenheit(tempC);
}

void setup()
{
  lastMessage = 0;
  Ethernet.begin(mac, ip);
  Serial.begin(115200);
  // incicializa a biblioteca sensors
  sensors.begin();
  //define a resolução
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
  delay(1000);
}

void loop()
{
  sensors.requestTemperatures();
  getTemperature(insideThermometer);
  Serial.println("Waiting Event...");
  // Serial.println(tempC);

  if (tempC >= HIGH_THRESHOLD && (millis() > (lastMessage + (EMAIL_INTERVAL * 1000))))
  {
    Serial.println("High Threshold Exceeded");
    char message1[] = "Temperature Sensor\0";
    char message2[] = "High Threshold Exceeded\0";
    sendEmail(subject, message1, message2, tempC);
  }
  else if (tempC <= LOW_THRESHOLD && (millis() > (lastMessage + (EMAIL_INTERVAL * 1000))))
  {
    Serial.println("Low Threshold Exceeded");
    char message1[] = "Temperature Sensor\0";
    char message2[] = "Low Threshold Exceeded\0";
    sendEmail(subject, message1, message2, tempC);
  }

  if (client.available())
  {
    checkEmail();
  }
}

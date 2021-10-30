// Projeto 46 - Ethernet Shield

#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// fio de dados é plugado ao pino 3 do Arduino
#define ONE_WIRE_BUS 3
#define TEMPERATURE_PRECISION 12

float tempC, tempF;

// prepara uma instância de OneWire para se comunicar com qualquer dispositivo OneWire
// (não apenas com CIs de temperatura Maxin/Dalas)

OneWire oneWire(ONE_WIRE_BUS);

// passa o endereço da instância oneWire ao Dallas Temperature

DallasTemperature sensors(&oneWire);

// arrays para armazenar os endereços dos dispositivos

DeviceAddress insideThermometer = {0x28, 0xAA, 0xC5, 0x30, 0x3E, 0x14, 0x01, 0x96};
DeviceAddress outsideThermometer = {0x28, 0xAA, 0xF3, 0x30, 0x42, 0x14, 0x01, 0xDA};

// configuração do Ethernet Shield

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {192, 168, 0, 175};
byte gateway[] = {192, 168, 0, 1};
byte subnet[] = {255, 255, 255, 0};
EthernetServer server(80);

void setup()
{
   // inicia a ethernet e o servidor
   Ethernet.begin(mac, ip, gateway, subnet);
   server.begin();
   // incicializa a biblioteca sensors
   sensors.begin();
   //define a resolução
   sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
   sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);
}

void loop()
{
   sensors.requestTemperatures();

   // escuta a entrada de clientes
   EthernetClient client = server.available();
   if (client)
   {
      // uma solicitação http termina com uma linha em branco
      boolean BlankLine = true;
      while (client.connected())
      {
         if (client.available())
         {
            char c = client.read();
            // se a linha estiver em branco e o fim da linha for um caractere newline
            // '\n' = fim da solicitação HTTP
            if (c == '\n' && BlankLine)
            {
               getTemperature(insideThermometer);
               // exibe a temperatura interna
               client.println("HTTP/1.1 200 OK"); // Resposta HTTP padrão
               client.println("Content-Type: text/html");
               client.println("\n");
               client.println("<!DOCTYPE html>");
               client.println("<html lang=\"pt-br\">");
               client.println("<head>");
               client.println("   <meta charset=\"UTF-8\">");
               client.println("   <meta http-equiv=\"refresh\" content=\"5\">");
               client.println("   <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
               client.println("   <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">");
               client.println("   <title>Arduino Web Server</title>");
               client.println("<body>");
               client.println("</head>");
               client.println("   <h1>Arduino Web Server</h1>");
               client.println("   <h2>Internal Temperature</h2>");
               client.println("      <p>");
               client.println("         Temp C: ");
               client.println(tempC);
               client.println("      </p>");
               client.println("      <p>");
               client.println("         Temp F: ");
               client.println(tempF);
               client.println("      </p><br/>");
               client.println("   <h2>External Temperature</h2>");
               client.println("      <p>");
               client.println("         Temp C: ");
               client.println(tempC);
               client.println("      </p>");
               client.println("      <p>");
               client.println("         Temp F: ");
               client.println(tempF);
               client.println("      </p>");
               client.println("</body>");
               client.println("</html>");

               break;
            }
            if (c == '\n')
            {
               // inciciando uma nova linha
               BlankLine = true;
            }
            else if (c != '\r')
            {
               // a linha atual tem um caractere nela
               BlankLine = false;
            }
         }
      }
      // permite um intervalo de tempo suficiente para que o navegador receba os dados
      delay(10);
      //fecha a conexão
      client.stop();
   }
}

// função para obter a temperatura de um dispositivo

void getTemperature(DeviceAddress deviceAddress)
{
   tempC = sensors.getTempC(deviceAddress);
   tempF = DallasTemperature::toFahrenheit(tempC);
}

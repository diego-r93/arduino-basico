// Projeto 50 - Leitor de RSS meteorológico

// Obtém a observação meteorológica atual da Base aérea de Edwards no site weather.gov,
// em formato XML.

// Esse código está longe de ser o melhor, certamente poderia ser refatorado

#include <Arduino.h>
#include <string.h>
#include <Ethernet.h>
#include <SPI.h>

// Comprimento máximo da string pode ter de ser ajustado, dependendo dos dados a serem extraídos
#define MAX_STRING_LEN 20

char tagStr[MAX_STRING_LEN] = "";
char dataStr[MAX_STRING_LEN] = "";
char tmpStr[MAX_STRING_LEN] = "";
char endTag[3] = {'<', '/', '\0'};
int len;

// Flags para diferenciar as tags XML dos elementos do documento (ou seja, dados)
boolean tagFlag = false;
boolean dataFlag = false;

// Variáveis da Ethernet
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
byte ip[] = {192, 168, 1, 175};
byte server[] = {140, 90, 113, 200}; // www.weather.gov

EthernetClient client;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting Weather RSS Reader");
  delay(1000);

  while (!client.connect(server, 80))
  {
    Serial.println("Connecting...");
    Ethernet.begin(mac, ip);

    if (client.connect(server, 80))
    {
      Serial.println("connected");
      Serial.println("Current weather at Edwards AFB:");
      client.println("GET /xml/current_obs/KEDW.xml HTTP/1.0");
      client.println();
      delay(2000);
    }
    else
    {
      Serial.println("connection failed");
    }
  }
}

void loop()
{
  // Lê os dados seriais na Web;
  while (client.available())
  {
    serialEvent();
  }

  if (!client.connected())
  {

    client.stop();

    for (int t = 0; t < 15; t++)
    {
      delay(60000); // 1 minute
    }

    if (client.connect(server, 80))
    {
      client.println("GET /xml/current_obs/KEDW.xml HTTP/1.0");
      client.println();
      delay(2000);
    }
    else
    {
      Serial.println("Reconnection failed");
    }
  }
}

// Processa cada caractere da Web
void serialEvent()
{
  char inChar = client.read();

  if (inChar == '<')
  {
    addChar(inChar, tmpStr);
    tagFlag = true;
    dataFlag = false;
  }
  else if (inChar == '>')
  {
    addChar(inChar, tmpStr);
    if (tagFlag)
    {
      strncpy(tagStr, tmpStr, strlen(tmpStr) + 1);
    }
    // Limpa o bufffer temporário
    clearStr(tmpStr);
    tagFlag = false;
    dataFlag = true;
  }
  else if (inChar != 10)
  {
    if (tagFlag)
    {
      // Adiciona o caractere da tag à string
      addChar(inChar, tmpStr);

      // Verifica a presença da tag de término </XML> e a ignora
      if (tagFlag && strcmp(tmpStr, endTag) == 0)
      {
        clearStr(tmpStr);
        tagFlag = false;
        dataFlag = false;
      }
    }
    if (dataFlag)
    {
      // Adicona caractere de dados à string
      addChar(inChar, dataStr);
    }
  }

  // Se for um LF, processa a linha
  if (inChar == 10)
  {
    // Encontra as tags específicas e imprime os dados
    if (matchTag("<temp_f>"))
    {
      Serial.print("TempF: ");
      Serial.print(dataStr);
    }
    if (matchTag("<tamp_c"))
    {
      Serial.print(", tempC: ");
      Serial.print(dataStr);
    }
    if (matchTag("<relative_humidity>"))
    {
      Serial.print(", Humidity: ");
      Serial.print(dataStr);
    }
    if (matchTag("<pressure_in>"))
    {
      Serial.print(", Pressure: ");
      Serial.print(dataStr);
      Serial.println("");
    }

    // Limpa todas as strings
    clearStr(tmpStr);
    clearStr(tagStr);
    clearStr(dataStr);

    // Limpa as Flags
    tagFlag = false;
    dataFlag = false;
  }
}

// Função para limpar uma string
void clearStr(char *str)
{
  int len = strlen(str);
  for (int c = 0; c < len; c++)
  {
    str[c] = 0;
  }
}

// Função para adicionar um caractere a uma string e verificar seu comprimento
void addChar(char ch, char *str)
{
  char *tagMsg = "<TRUNCATED_TAG>";
  char *dataMsg = "-TRUNCATED_DATA-";

  // Verifica o tamanha máximo da string, para se certificar de que ela não é
  // grande demais. Caso a string ultrapasse MAX_STRING_LEN, presume que esses dados
  // não são importantes e substitui-os por uma mensagem alerta
  if (strlen(str) > MAX_STRING_LEN - 2)
  {
    if (tagFlag)
    {
      clearStr(tagStr);
      strcpy(tagStr, tagMsg);
    }
    if (dataFlag)
    {
      clearStr(dataStr);
      strcpy(dataStr, dataMsg);
    }
    // Limpa o buffer temporário e as flags para interromper o processamento atual
    clearStr(tmpStr);
    tagFlag = false;
    dataFlag = false;
  }
  else
  {
    // Adiciona um caractere à string
    str[strlen(str)] = ch;
  }
}

// Função para verificar a tag atual de uma string especifica
boolean matchTag(char *searchTag)
{
  if (strcmp(tagStr, searchTag) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }

  // Assim ficaria melhor, eu acho...
  // return (strcmp(tagStr, searchTag) == 0) ? true : false;
}

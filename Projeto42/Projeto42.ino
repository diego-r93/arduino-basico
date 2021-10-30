// Projeto 42 - Operação simples de leitura/escrita em um cartão SD

#include <SD.h>

const int csPin = 18;

File File1;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }; // Espera que a porta serial se conecte (ATmega32u4)

  Serial.println("Initializing the SD Card...");

  if (!SD.begin(csPin))
  {
    Serial.println("Initialization Failed!");
    return;
  }

  Serial.println("Initialization Complete.\n");

  Serial.println("Looking for the file 'testfile.txt'...\n");

  if (SD.exists("testfile.txt"))
    Serial.println("testfile.txt already exists.\n");
  else
  {
    Serial.println("testfile.txt doesn't exist.");
    Serial.println("Creating file testfile.txt...\n");
  }

  File1 = SD.open("testfile.txt", FILE_WRITE);
  File1.close();

  Serial.println("Writing text to file...");
  String dataString;
  File1 = SD.open("testfile.txt", FILE_WRITE);

  if (File1)
  {
    for (byte i = 1; i < 11; i++)
    {
      dataString = "Test Line ";
      dataString += i;
      File1.println(dataString);
    }
    Serial.println("Text written to file...\n");
  }

  File1.close();

  Serial.println("Reading contents of textfile.txt...");
  File1 = SD.open("testfile.txt");

  if (File1)
  {
    while (File1.available())
      Serial.write(File1.read());

    File1.close();
  }
  else
    Serial.println("Error opening testfile.txt");

  //delete the file;
  Serial.println("\nDeleting testfile.txt...\n");
  SD.remove("testfile.txt");

  Serial.println(SD.exists("testfile.txt") ? "testfile.txt still exists." : "testfile.txt has been deleted.");
}

void loop()
{
  // não há nada aqui
}

// Projeto 26 - Controle de um servo duplo

#include <Servo.h>

char buffer[11];
Servo servo1; // Cria um objeto servo
Servo servo2; // Cria um segundo objeto servo

void setup()
{
  servo1.attach(5); // Anexa o servo, no pino 5, ao objeto servo1
  servo2.attach(6); // Anexa o servo, no pino 6, ao objeto servo2
  Serial.begin(9600);

  while (Serial.available())
    Serial.read();

  servo1.write(90); // Coloca o servo1 na posição inicial
  servo2.write(90); // Coloca o servo2 na posição inicial
  Serial.println("STARTING...");
}

void loop()
{
  if (Serial.available() > 0) // Verifica se dados foram digitados
  {
    byte index = 0;
    delay(100);                       // Deixa o buffer encher
    int numChar = Serial.available(); // Encontra o comprimento da string

    if (numChar > 10)
      numChar = 10;

    while (numChar--)
      buffer[index++] = Serial.read(); // Preenche o buffer com a string

    buffer[index] = '\0';
    splitString(buffer);
  }
}

void splitString(char *data)
{
  char *parameter;
  Serial.print("Data entered: ");
  Serial.print(data);
  parameter = strtok(data, " ,"); // Procura um vírgula ou um espaço em branco

  while (parameter != NULL) // Se ainda não atingimos o fim da string
  {
    setServo(parameter);            // Executa a função setServo
    parameter = strtok(NULL, " ,"); // Continua à partir de uma vírgula ou espaço em branco
  }

  while (Serial.available())
    Serial.read();
}

void setServo(char *data)
{
  int firstVal, secondVal;

  if ((data[0] == 'L') || (data[0] == 'l'))
  {
    firstVal = strtol(data + 1, NULL, 10);  // Converte uma string para long int
    firstVal = constrain(firstVal, 0, 180); // Restringe os valores entre 0 e 180
    servo1.write(firstVal);
    Serial.print("Servo1 is set to: ");
    Serial.println(firstVal);
  }

  if ((data[0] == 'R') || (data[0] == 'r'))
  {
    secondVal = strtol(data + 1, NULL, 10);   // Converte uma string para long int
    secondVal = constrain(secondVal, 0, 180); // Restringe os valores entre 0 e 180
    servo2.write(secondVal);
    Serial.print("Servo2 is set to: ");
    Serial.println(secondVal);
  }
}

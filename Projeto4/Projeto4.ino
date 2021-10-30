// Projeto 4 -  Semáforo Interativo

byte carRedPin = 12;
byte carYellowPin = 11;      // semáforo para carros
byte carGreenPin = 10;

byte pedRedPin = 9;
byte pedGreenPin = 8;        // semáforo para pedestres
byte pushButton = 2;

unsigned crossTime = 5000;   // tempo para que os pedestres atravessem
unsigned long changeTime;    // tempo desde a conclusão do último ciclo para pedestres

void 
setup()
{
  pinMode (carRedPin, OUTPUT);
  pinMode (carYellowPin, OUTPUT);
  pinMode (carGreenPin, OUTPUT);
  pinMode (pedRedPin, OUTPUT);
  pinMode (pedGreenPin, OUTPUT);
  pinMode (pushButton, INPUT);

  digitalWrite (carGreenPin, HIGH);
  digitalWrite (carYellowPin, LOW);
  digitalWrite (carRedPin, LOW);
}

void
loop()
{
  boolean state = digitalRead (pushButton);
  
  // verifica se o botão foi pressionado e se transcorreram 10 segundos desde a última vez que isso ocorreu 
    
  if (state == HIGH && (millis() - changeTime) > 5000)
    changeLights();  // chama a função para alterar as luzes
}

void changeLights()
{
  digitalWrite (carGreenPin, LOW);     
  digitalWrite (carYellowPin, HIGH);
  delay (2000);

  digitalWrite (carYellowPin, LOW);
  digitalWrite (carRedPin, HIGH);
  delay (1000);

  digitalWrite (pedRedPin, LOW);
  digitalWrite (pedGreenPin, HIGH);
  delay (crossTime);

  for (int x = 0; x < 10; x++)
  {
      digitalWrite (pedGreenPin, HIGH);
      delay (250);
      digitalWrite (pedGreenPin, LOW);
      delay (250);
  }

  digitalWrite (pedRedPin, HIGH);
  delay (1000);

  digitalWrite (carRedPin, LOW);
  digitalWrite (carGreenPin, HIGH);

  changeTime = millis();
}

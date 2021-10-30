// Projeto 16 - Uso do CI controlador de motor L293D

#define SWITCH_PIN 2 // Entrada da chave
#define MOTOR_PIN1 3 // Entrada 1 do L293D
#define MOTOR_PIN2 4 // Entrada 2 do L293D
#define SPEED_PIN 9  // Pino de ativação 1 do L293D
#define POT_PIN 0    // Potenciômetro no pino analógico 0

int mSpeed = 0; // Variável para armazenar o valor de velocidade atual

void setup()
{
  pinMode(SWITCH_PIN, INPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(SPEED_PIN, OUTPUT);
}

void loop()
{
  mSpeed = analogRead(POT_PIN) / 4; // lé o valor de velocidade a partir do potenciômetro
  analogWrite(SPEED_PIN, mSpeed);   // escreve a velocidade para o pino de ativação 1

  if (digitalRead(SWITCH_PIN)) // se a chave estiver em HIGH gire o motor em sentido horário
  {
    digitalWrite(MOTOR_PIN1, LOW);  // define a entrada 1 do L293D como baixa
    digitalWrite(MOTOR_PIN2, HIGH); // define a entrada 2 do L293D como alta
  }
  else // se a chave estiver em LOW gire o motor em sentido anti-horário
  {
    digitalWrite(MOTOR_PIN1, HIGH); // define a entrada 1 do L293D como alta
    digitalWrite(MOTOR_PIN2, LOW);  // define a entrada 2 do L293D como baixa
  }
}

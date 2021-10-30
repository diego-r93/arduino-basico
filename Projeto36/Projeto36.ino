// Projeto 36 - Sensor serial de temperatura

#define SENSOR_PIN 0

float Celsius, Fahrenheit, Kelvin;
int sensorValue;

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialising.....");
}

void loop()
{
  GetTemp();
  Serial.print("Celsius: ");
  Serial.println(Celsius);
  Serial.print("Fahrenheit: ");
  Serial.println(Fahrenheit);
  Serial.println();
  delay(1000);
}

void GetTemp()
{
  sensorValue = analogRead(SENSOR_PIN);               // lê o sensor
  Kelvin = (((float(sensorValue) / 1023) * 5) * 100); // converte em Kelvin
  Celsius = Kelvin - 273.15;                          // converte em Celsius
  Fahrenheit = (Celsius * 1.8) + 32;                  // converte em Fahrenheit
}

//https://www.youtube.com/watch?v=2tdsg_K-oQQ
//Descargar biblioteca DHT sensor library
//Descargar biblioteca Adafruit Unified Sensor

#include <DHT.h>
#include <DHT_U.h>

int sensor =2;
int temperatura;
int humedad;

DHT dht(sensor, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  temperatura=dht.readTemperature();
  humedad=dht.readHumidity();
  Serial.print("\n Temperatura: ");
  Serial.print(temperatura);
  Serial.print("\n Humedad: ");
  Serial.print(humedad);
  delay(500);
}

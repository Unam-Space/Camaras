#include <Wire.h>
#include <HMC5883L.h>
 
HMC5883L compass;
 
int previousDegree;
 
void setup()
{
  Serial.begin(9600);
 
  /// Inicializar HMC5883L
  Serial.println("Initialize HMC5883L");
  while (!compass.begin())
  {
    Serial.println("Nie odnaleziono HMC5883L, sprawdz polaczenie!");
    delay(500);
  }
 
  // Establecer el rango de medición
  compass.setRange(HMC5883L_RANGE_1_3GA);
 
  // Establecer el modo de operación
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
 
  // Establecer la frecuencia de medición
  compass.setDataRate(HMC5883L_DATARATE_15HZ);
 
  // Número de muestras promediadas
  compass.setSamples(HMC5883L_SAMPLES_4);
}
 
void loop()
{
  // Obtener los vectores normalizados
  Vector norm = compass.readNormalize();
 
  // Cálculo de dirección (rad)
  float heading = atan2(norm.YAxis, norm.XAxis);
 
  // Estableciendo el ángulo de declinación para Bytom 4'26E (positivo)
  // Fórmula: (grados + (min / 60.0)) / (180 / M_PI);
   float declinationAngle = ( 46.0 + ( 50.0 / 60.0 ) ) / ( 180 / M_PI ) ;
  heading += declinationAngle;
 
   // corrección cat.
  if (heading < 0)
  {
    heading += 2 * PI;
  }
 
  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }
 
  //Convertir radianes a grados
  float headingDegrees = heading * 180/M_PI;
 
  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();
 
  delay(100);
 
  delay(100);
}

#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

//Variables sensor humedad y temperatura relativos
int sensor=2;
int temperatura;
int humedad;
 

DHT dht(sensor, DHT11);

//Variable sensor humedad 
int sensorHumedad = A0;

//Brujula
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);



void setup() {
  Serial.begin(9600);
  
  pinMode(13,OUTPUT);
  dht.begin();

  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  if(!mag.begin())
  {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  displaySensorDetails();
  
}

void loop() {
  sensor_humedad_relativa();
  sensor_humedad();
  sensor_brujula();
  marker();

}



void sensor_humedad_relativa(void){
  
  temperatura=dht.readTemperature();
  humedad=dht.readHumidity();
  Serial.print("////////////////////////////////////////////////////////////////////////");
  Serial.println("\n\t\t Sensor Temperatura y humedad relativa");
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Humedad: ");
  Serial.println(humedad);
  Serial.println("////////////////////////////////////////////////////////////////////////");
  delay(1000);
  }

void sensor_humedad(void){

  Serial.print("////////////////////////////////////////////////////////////////////////");
  Serial.print("\n\t\t Sensor humedad ");
  Serial.print("Humedad: ");
  Serial.println(humedad);

  if(humedad >= 460 ){
  digitalWrite(13,HIGH);
  }
  else{
  digitalWrite(13,LOW);
  }
  Serial.println("////////////////////////////////////////////////////////////////////////");
  delay(1000);
}



void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.print("Datos de la brujula\n");
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void sensor_brujula(void){
    

  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = 0.22;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  
  delay(1000);
}

void marker(void){
  if(!Serial.available())
    return;

  char serialListener = Serial.read();
  Serial.print("/////////////////////////////////////////////");
  Serial.println(serialListener);

  for(int i; i < 10; i++)
  {
    char serialListener = Serial.read();
    int serialF = serialListener - '0';

    Serial.println(serialF);

  }
}

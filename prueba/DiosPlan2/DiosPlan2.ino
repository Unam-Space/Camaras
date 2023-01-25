#include <Separador.h>
#include <Wire.h>
#include <math.h>


//Variables sensor humedad y temperatura relativos
Separador s;
String aruco;
char vectorX[10];
int numeroX = 0;
char vectorY[10];
int numeroY = 0;
char vectorZ[10];
int numeroZ = 0;


void setup() {
  Serial.begin(9600);
  

}

void loop() {
  
  if(Serial.available()){
    aruco = Serial.readString();

    String coorX = s.separa(aruco, ',', 0);
    String coorY = s.separa(aruco, ',', 1);
    String coorZ = s.separa(aruco, ',', 2);

    coorX.toCharArray(vectorX,10);
    numeroX = atoi(vectorX);

    coorY.toCharArray(vectorY,10);
    numeroY = atoi(vectorY);

    coorZ.toCharArray(vectorZ,10);
    numeroZ = atoi(vectorZ);


    Serial.print("La coordenada X es: ");
    Serial.println(numeroX);
    Serial.print("La coordenada Y es: ");
    Serial.println(numeroY);
    Serial.print("La coordenada Z es: ");
    Serial.println(numeroZ);
    
  }
}

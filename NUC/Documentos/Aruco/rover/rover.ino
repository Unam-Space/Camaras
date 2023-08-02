#include <Separador.h>
#include <Wire.h>
#include <math.h>
#include <SoftwareSerial.h> //utilizando la app Arduino BlueControl se ingresan los números como "2" ó '2'
SoftwareSerial miBT(9,11);// (receptor de arduino, transmisor de arduino) 
char dato;
String voice;
float VelocidadDerecha=125.0;
float VelocidadIzquierda=125.0;
int Q = 1;
//Variables sensor humedad y temperatura relativos
Separador s;
String aruco;
char vectorX[10];
double numeroX = 0.0;
char vectorY[10];
int numeroY = 0;
char vectorZ[10];
double numeroZ = 0.0;
double anguloRadianes = 0.0;
double anguloGrados = 0.0;
//variables Motores
int MotorIzquierdoAdelante  = 3; //pin Digital
int MotorIzquierdoAtras     = 4; //pin Digital
int MotorDerechoAdelante    = 7; //pin Digital
int MotorDerechoAtras       = 8; //pin Digital
int pinVelocidadDerecha     = 6; //pin PWM
int pinVelocidadIzquierda   = 5; //pin PWM
int velocidad = 125;//velocidad motores(0-255)

void setup() { 
  Serial.begin(9600);
  //miBT.begin(9600);//velocidad por default
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  delay(5000);
  digitalWrite(13,LOW);
//activar señales del puente h
  pinMode(MotorIzquierdoAdelante,OUTPUT);
  pinMode(MotorDerechoAdelante,OUTPUT);
  pinMode(MotorIzquierdoAtras,OUTPUT);
  pinMode(MotorDerechoAtras,OUTPUT);

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


    anguloRadianes = atan((double)((-numeroX)/(numeroZ)));
    anguloGrados = 180*(double)anguloRadianes/PI;
    Serial.println(anguloRadianes);
    Serial.println(anguloGrados);
    Serial.println(numeroX);
    Serial.println(numeroZ);
    
  }
  //manda señales PWM de la velocidad al puente H
  analogWrite(pinVelocidadDerecha,velocidad);
  analogWrite(pinVelocidadIzquierda,velocidad);

  
  /*if(miBT.available()){   //lee bt y envia a arduino
    Serial.write(miBT.read());  
    dato = miBT.read();
    Serial.println(miBT.read());
    }
  if(Serial.available()){
    miBT.write(Serial.read());
    voice =Serial.readString();
    }
    delay(2);
  if(dato == '1'){
    carroAvanzaAdelante();
    
    }
  if(dato=='2') 
    carroAvanzaAtras();
    
  if(dato=='3') 
      carroGiraIzquierda();
    
  if(dato=='4')
      carroGiraDerecha();
      
  if(dato=='5')
      pruebaMotores();
  
  Serial.println(dato); */
  carroAvanzaAdelante();
    
}





//FUNCIONES
void carroAvanzaAdelante(){
    if(anguloGrados < 10){      
    Serial.println("gira a la Derecha");
    analogWrite(pinVelocidadDerecha,VelocidadDerecha+anguloGrados*Q);
    analogWrite(pinVelocidadIzquierda,VelocidadIzquierda-anguloGrados*Q);
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,HIGH);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,LOW);
    delay(1000);
    //carroDetenido();
    delay(10);
    }

    else if (anguloGrados > 20){
    Serial.println("Gira a la Izquierda");
    analogWrite(pinVelocidadDerecha,VelocidadDerecha+anguloGrados*Q);
    analogWrite(pinVelocidadIzquierda,VelocidadIzquierda-anguloGrados*Q);
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,HIGH);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,LOW);
    delay(1000);
    //carroDetenido();
    delay(10);
    }

    else if (anguloGrados > 10 && anguloGrados < 20){
    Serial.println("avanzando hacia adelante");
    analogWrite(pinVelocidadDerecha,VelocidadDerecha);
    analogWrite(pinVelocidadIzquierda,VelocidadIzquierda);
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,HIGH);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,LOW);
    delay(1000);
    //carroDetenido();
    delay(10);}
        
  }
  
void carroAvanzaAtras(){
    Serial.println("avanzando hacia atras");
    digitalWrite(MotorDerechoAdelante,LOW);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,HIGH);
    digitalWrite(MotorIzquierdoAtras,HIGH);
    delay(1000);
    carroDetenido();
    delay(10);
  }
  
void carroGiraDerecha(){
    Serial.println("girando a la derecha");
    digitalWrite(MotorDerechoAdelante,LOW);
    digitalWrite(MotorIzquierdoAdelante,HIGH);
    digitalWrite(MotorDerechoAtras,HIGH);
    digitalWrite(MotorIzquierdoAtras,LOW);
    digitalWrite(13,HIGH);
  }
  
void carroGiraIzquierda(){
    Serial.println("girando a la izquierda");
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,HIGH);
    digitalWrite(13,LOW);
  }
  
void carroDetenido(){
    Serial.println("automovil detenido");
    digitalWrite(MotorDerechoAdelante,LOW);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,LOW);
    digitalWrite(MotorIzquierdoAtras,LOW);
  }
void pruebaMotores(){
    Serial.println("automovil detenido");
    digitalWrite(MotorDerechoAdelante,HIGH);
    digitalWrite(MotorIzquierdoAdelante,LOW);
    digitalWrite(MotorDerechoAtras,HIGH);
    digitalWrite(MotorIzquierdoAtras,LOW);
    delay(200);
    velocidad = velocidad+1;
    if (velocidad == 250){
      velocidad = 0;
      }
  }

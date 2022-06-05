 /* MOSI - pin 11
    MISO - pin 12
    CLK - pin 13
    CS - pin 4    
    humedad - pin 2
    temperatura - pin A0  */

#include <SPI.h>                                            //Libreria tarjeta SD
#include <SD.h>                                             //       "
#include <DHT.h>                                            //Librerias humedad
#include <DHT_U.h>                                          //       "

#define pul 7                                               //Pulsador


int SENSORHUM = 2;
float HUMEDAD;
DHT dht (SENSORHUM, DHT22);

unsigned long tiempo = millis ();                           //Variable que almacena la función millis.

int SENSORTEM;
float TEMPERATURA;

int TRIG = 10;
int ECO = 9;
int DURACION;
int DISTANCIA;

struct mediciones {
  struct temperatura {
    uint16_t valortemp;
    uint32_t tiempotemp;
    char indictemp = 'T';
  }temperatura;
  struct humedad {
    uint16_t valorhum;
    uint32_t tiempohum;
    char indichum = 'H';
  }humedad; 
  struct ultrasonido {
    uint16_t valorult;
    uint32_t tiempoult;
    char indicult = 'U';
  }ultrasonido; 
}mediciones;


File myFile;                                                //declarar myFile

void setup() {
  
  struct mediciones med[5];
  Serial.begin(9600);
  
  dht.begin ();                                             //Inicialización del sensor de humedad

  SENSORTEM = analogRead (A0);                              //Sensor temperatura
  
  pinMode (TRIG, OUTPUT);
  pinMode (ECO, INPUT);
  
  Serial.print("Iniciando la SD card...");
  if (!SD.begin(4)) {
    Serial.println("Iniciacion fallida!");
    while (1); }
  Serial.println("Iniciacion correcta.");

}

void loop() {

if (digitalRead(pul)){
  for (int i=1; i<=24; i++) {
  unsigned long tiempo0 = (millis() - tiempo);              //Variable que pone el tiempo en 0 y así comienza con cada medición.
  
  struct mediciones med;
  delay(100);
  myFile = SD.open("archivo.dat", FILE_WRITE);              //Crear archivo

    myFile.print("Hora: ");
    myFile.print(i);
    myFile.print(") ");
 
//Humedad--------------------------------------------------       
    mediciones.humedad.indichum = 'H';
    mediciones.humedad.valorhum = dht.readHumidity (SENSORHUM);
    mediciones.humedad.tiempohum = (millis() - tiempo0);              //Tiempo total menos el detectado al principio
    myFile.print("Humedad(");
    myFile.print(mediciones.humedad.indichum);
    myFile.print(")");
    myFile.print(": ");
    myFile.print(mediciones.humedad.valorhum);
    myFile.print("  ");
//Temperatura----------------------------------------------   
    mediciones.temperatura.indictemp = 'T';
    mediciones.temperatura.valortemp = ((SENSORTEM * 5000.0) / 1024) /10;
    mediciones.temperatura.tiempotemp = (millis() - tiempo0);
    
    myFile.print("Temperatura(");
    myFile.print(mediciones.temperatura.indictemp);
    myFile.print(")");
    myFile.print(": ");
    myFile.print(mediciones.temperatura.valortemp);
    myFile.print("  ");
//Ultrasonido----------------------------------------------
    digitalWrite (TRIG, HIGH);
    delay (1);
    digitalWrite (TRIG, LOW);
  
    DURACION = pulseIn (ECO, HIGH);
    DISTANCIA = DURACION / 58.2;

    mediciones.ultrasonido.indicult;
    mediciones.ultrasonido.valorult = DISTANCIA;
    mediciones.ultrasonido.tiempoult = (millis() - tiempo0);
    
    myFile.print("Distancia(");
    myFile.print(mediciones.ultrasonido.indicult);
    myFile.print(")");
    myFile.print(": ");
    myFile.print(mediciones.ultrasonido.valorult);
    myFile.print("Tiempo desde la última medición: ");
    myFile.print(millis() - tiempo0);
//---------------------------------------------------------
 
  } 
  myFile.close();} //cerrar el archivo

}
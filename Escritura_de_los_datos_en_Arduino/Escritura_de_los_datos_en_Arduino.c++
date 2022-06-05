 /* MOSI - pin 11
    MISO - pin 12
    CLK - pin 13
    CS - pin 4    
    humedad - pin 2
    temperatura - pin A0  */

#include <SPI.h>   //libreria tarjeta SD
#include <SD.h>    //       "
#include <DHT.h>   //librerias humedad
#include <DHT_U.h> //       "

#define pul 7      //pulsador

unsigned long t;

int SENSORHUM = 2;
float HUMEDAD;
DHT dht (SENSORHUM, DHT22);

int SENSORTEM;
float TEMPERATURA;

struct mediciones {
  struct sensores {
    uint16_t valor;
    uint32_t tiempo;
    char indic;
  } humedad, temperatura; 
};

unsigned long tiempo_sensores = 0;

File myFile;  //declarar myFile

void setup() {
  
  struct mediciones med[5];
  Serial.begin(9600);
  
  dht.begin ();                   //sensor humedad

  SENSORTEM = analogRead (A0);                      //sensor temperatura
  
  Serial.print("Iniciando la SD card...");
  if (!SD.begin(4)) {
    Serial.println("Iniciacion fallida!");
    while (1); }
  Serial.println("Iniciacion correcta.");

}

void loop() {

if (digitalRead(pul)){

  struct mediciones med;
  delay(100);
  myFile = SD.open("archivo.dat", FILE_WRITE); //crear archivo

    med.humedad.indic = 'H';
    med.humedad.valor = dht.readHumidity (SENSORHUM);
    med.humedad.tiempo = millis() - tiempo_sensores;
    
    med.temperatura.indic = 'T';
    med.temperatura.valor = ((SENSORTEM * 5000.0) / 1024) /10;
    med.temperatura.tiempo = med.humedad.tiempo;
    
    tiempo_sensores = millis();
 
  myFile.write((const uint8_t *)&med, sizeof(med));
  
  myFile.close();} //cerrar el archivo

}
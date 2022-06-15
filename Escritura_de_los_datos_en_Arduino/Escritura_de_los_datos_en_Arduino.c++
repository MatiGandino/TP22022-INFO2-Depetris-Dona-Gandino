
#include <SPI.h>         //Libreria tarjeta SD
#include <SD.h>          //       "
#include <DHT.h>         //Librerias humedad
#include <DHT_U.h>       //       "
#include <stdint.h> 
#define pul 7            //Pulsador
#define SENSORHUM 2
#define SENSORTEM A0

DHT dht (SENSORHUM, DHT22);

unsigned long tiempo0;                           //Variable que almacena la función millis. 
File myFile;                                     //declarar myFile

float TEM;      //Valor analogico sensor temperatura

int TRIG = 10;        //Disparador sensor ultrasonido
int ECO = 9;          //Receptor sensor ultrasonido
int DURACION;         //Variable que almacena el tiempo de rebote (ultrasonido)
int DISTANCIA;        //Calculo de distancia (ultrasonido)

struct mediciones {        
  struct temperatura {
    uint32_t tiempo;
    uint16_t valor;
    char indic;
    char temp;
  }temperatura, humedad, ultrasonido;
}mediciones;

struct mediciones med;       //Declaracion de estructura

void setup(){
  Serial.begin(9600);        //Inicializar el monitor serie
  
  dht.begin ();              //Inicialización del sensor de humedad
  
  pinMode (TRIG, OUTPUT);    //Salida ultrasonido
  pinMode (ECO, INPUT);      //Entrada ultrasonido
  
  Serial.print("Iniciando la SD card...");
  if (!SD.begin(4)) {
    Serial.println("Iniciacion fallida!");
    while(1); }
  Serial.println("Iniciacion correcta.");

  tiempo0 = 0;       //Inicializamos tiempo
}

void loop() {
  TEM = analogRead(SENSORTEM);           //Sensor temperatura

  digitalWrite(TRIG, HIGH);
  delay (1);                            //Funcionamiento sensor ultrasonido
  digitalWrite (TRIG, LOW);
  
  DURACION = pulseIn (ECO, HIGH);       //               "
  DISTANCIA = DURACION / 58.2;

if (digitalRead(pul)){                  //Evalua el estado del pulsador

      myFile = SD.open("archivo.dat", FILE_WRITE);             //Crear archivo
     
  //Datos de sensor humedad--------------------------------------------------      
      med.humedad.valor = dht.readHumidity (SENSORHUM);
      med.humedad.tiempo = millis() - tiempo0;
      med.humedad.indic = 'H';
  
  //Datos de sensor temperatura----------------------------------------------   
      med.temperatura.valor = ((TEM * 5000.0) / 1024)/10;
      med.temperatura.tiempo = millis() - tiempo0;
      med.temperatura.indic = 'T';
  
  //Datos de sensor ultrasonido----------------------------------------------
      med.ultrasonido.valor = DISTANCIA;
      med.ultrasonido.tiempo = millis() - tiempo0;
      med.ultrasonido.indic = 'U';
  
  //-------------------------------------------------------------------------
      tiempo0 = millis();          //Valorizacion tiempo respecto a millis
      
      delay(200);                  //Antirrebote
      
      Serial.println("Escribiendo SD Card...");             //Comprobamos la correcta escritura
      
      myFile.write((const uint8_t *)&med, sizeof(med));     //Subida de los datos al SD
      myFile.close();                                       //Cerramos el archivo
      
  }
}

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
    uint32_t tiempotemp;
    uint16_t valortemp;
    char indictemp = 'T';
    char temp;
  }temperatura;
  struct humedad {
    uint32_t tiempohum;
    uint16_t valorhum;
    char indichum = 'H';
    char hum;
  }humedad; 
  struct ultrasonido {
    uint32_t tiempoult;
    uint16_t valorult;
    char indicult = 'U';
    char ultra;
  }ultrasonido; 
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
      med.humedad.valorhum = dht.readHumidity (SENSORHUM);
      med.humedad.tiempohum = millis() - tiempo0;
      med.humedad.indichum = 'H';
  
  //Datos de sensor temperatura----------------------------------------------   
      med.temperatura.valortemp = ((TEM * 5000.0) / 1024)/10;
      med.temperatura.tiempotemp = millis() - tiempo0;
      med.temperatura.indictemp = 'T';
  
  //Datos de sensor ultrasonido----------------------------------------------
      med.ultrasonido.valorult = DISTANCIA;
      med.ultrasonido.tiempoult = millis() - tiempo0;
      med.ultrasonido.indicult = 'U';
  
  //-------------------------------------------------------------------------
      tiempo0 = millis();          //Valorizacion tiempo respecto a millis
      
      delay(200);                  //Antirrebote
      
      Serial.println("Escribiendo SD Card...");             //Comprobamos la correcta escritura
      
      myFile.write((const uint8_t *)&med, sizeof(med));     //Subida de los datos al SD
      myFile.close();                                       //Cerramos el archivo
      
  }
}
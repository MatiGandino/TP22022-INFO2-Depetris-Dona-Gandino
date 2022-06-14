#include <stdio.h>
#include <stdint.h> //Para utilizar uint16_t y uint32_t.
#define c 24	    //Declaracion de "c" para utilizar en el for.

typedef struct mediciones { 			//Estructura que almacena los valores leídos.
	struct temperatura {
		uint32_t tiempotemp;		//Variable Tiempo.
		uint16_t valortemp;		//Variable Valor del sensor.
		char indictemp;			//Variable de la letra del sensor.
		char temp;
	}temperatura;
	struct humedad {
		uint32_t tiempohum;
		uint16_t valorhum;
		char indichum;
		char hum;
	}humedad; 
	struct ultrasonido {
		uint32_t tiempoult;
		uint16_t valorult;
		char indicult;
		char temp;
	}ultrasonido; 
}mediciones;

int main() {
	
	mediciones med[c];
	
	FILE *fpt;
	
	fpt = fopen("D:/Rafael/Desktop/ARCHIVO.dat", "r");      //Lectura del archivo.
	
	if(fpt == NULL){
		printf("\n  Error al abrir el archivo...");	//Si hay algún problema, mensiona que hay un problema con la lectura.
		return -1;
	}
	
	printf("Apertura del archivo exitosa...\n\n");
	
	fread(med, sizeof(mediciones), c, fpt); 		//Lectura de todos los valores del archivo.
	fclose (fpt);
	

	for (int i = 0; i < c; i++){				//For para escribir los datos leídos.
		printf ("Hora %d:\n", i+1);
		printf ("  Sensor: Temperatura(%c). \n  Valor: %d°C.\n  Tiempo desde la ultima medicion: %d ms.\n\n", med[i].temperatura.indictemp, med[i].temperatura.valortemp, med[i].temperatura.tiempotemp);
		printf ("  Sensor: Humedad(%c). \n  Valor: %d÷.\n  Tiempo desde la ultima medicion: %d ms.\n\n", med[i].humedad.indichum, med[i].humedad.valorhum, med[i].humedad.tiempohum)  ;
		printf ("  Sensor: Distancia(%c). \n  Valor: %dcm.\n  Tiempo desde la ultima medicion: %d ms.\n\n\n", med[i].ultrasonido.indicult, med[i].ultrasonido.valorult, med[i].ultrasonido.tiempoult);
	};
	
	return 0;
}

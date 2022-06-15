#include <stdio.h>
#include <stdint.h> //Para utilizar uint16_t y uint32_t.
#define c 24	    //Declaracion de "c" para utilizar en el for.

typedef struct mediciones { 			//Estructura que almacena los valores leídos.
	struct temperatura {
		uint32_t tiempo;       //Variable Tiempo.
		uint16_t valor;        //Variable Valor del sensor.
		char indic;            //Variable de la letra del sensor.
		char temp;
	}temperatura, humedad, ultrasonido;
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
		
	for (int i = 0; i < c; i++){    //For para escribir los datos leídos.
		printf ("  Sensor: %c \n  Valor: %d \n  Tiempo desde la ultima medicion: %d\n\n", med[i].humedad.indic, med[i].humedad.valor, med[i].humedad.tiempo);
		printf ("  Sensor: %c \n  Valor: %d \n  Tiempo desde la ultima medicion: %d\n\n", med[i].temperatura.indic, med[i].temperatura.valor, med[i].temperatura.tiempo);
		printf ("  Sensor: %c \n  Valor: %d \n  Tiempo desde la ultima medicion: %d\n\n\n", med[i].ultrasonido.indic, med[i].ultrasonido.valor, med[i].ultrasonido.tiempo);
	};
	
	return 0;
}

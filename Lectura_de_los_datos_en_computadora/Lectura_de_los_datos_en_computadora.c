#include <stdio.h>
#include <stdint.h> //para utilizar uint16_t y uint32_t
#define c 24

typedef struct mediciones {
	struct temperatura {
		uint32_t tiempotemp;
		uint16_t valortemp;
		char indictemp;
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
	
	fpt = fopen("D:/Rafael/Desktop/ARCHIVO.dat", "r");      //Agregar la direccion del archivo.
	
	if(fpt == NULL){
		printf("\n  Error al abrir el archivo...");
		return -1;
	}
	
	printf("Apertura del archivo exitosa...\n\n");
	
	fread(med, sizeof(mediciones), c, fpt);
	fclose (fpt);
	

	for (int i = 0; i < c; i++){
		printf ("Hora %d:\n", i+1);
		printf ("  Sensor: Temperatura(%c). \n  Valor: %d°C.\n  Tiempo desde la ultima medicion: %d ms.\n\n", med[i].temperatura.indictemp, med[i].temperatura.valortemp, med[i].temperatura.tiempotemp);
		printf ("  Sensor: Humedad(%c). \n  Valor: %d÷.\n  Tiempo desde la ultima medicion: %d ms.\n\n", med[i].humedad.indichum, med[i].humedad.valorhum, med[i].humedad.tiempohum)  ;
		printf ("  Sensor: Distancia(%c). \n  Valor: %dcm.\n  Tiempo desde la ultima medicion: %d ms.\n\n\n", med[i].ultrasonido.indicult, med[i].ultrasonido.valorult, med[i].ultrasonido.tiempoult);
	};
	
	return 0;
}

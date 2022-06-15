#include <stdio.h>
#include <stdint.h> //para utilizar uint16_t y uint32_t
#define c 5

typedef struct mediciones {
	struct temperatura {
		uint32_t tiempo;
		uint16_t valor;
		char indic;
		char temp;
	}temperatura, humedad, ultrasonido;
}mediciones;

int main() {

	mediciones med[c];
	
	FILE *fpt;
	
	fpt = fopen("ARCHIVO.dat", "r");
	
	if(fpt == NULL){
		printf("\n  Error al abrir el archivo...");
		return -1;
	}
		
	printf("\n  Apertura del archivo exitosa...\n\n");
	
	fread(med, sizeof(mediciones), c, fpt);
	fclose (fpt);
		
	for (int i = 0; i < c; i++){
		printf ("  Sensor: %c \n  Valor: %d \n  Tiempo desde la ultima medicion: %d\n\n", med[i].humedad.indic, med[i].humedad.valor, med[i].humedad.tiempo);
		printf ("  Sensor: %c \n  Valor: %d \n  Tiempo desde la ultima medicion: %d\n\n", med[i].temperatura.indic, med[i].temperatura.valor, med[i].temperatura.tiempo);
		printf ("  Sensor: %c \n  Valor: %d \n  Tiempo desde la ultima medicion: %d\n\n\n", med[i].ultrasonido.indic, med[i].ultrasonido.valor, med[i].ultrasonido.tiempo);
	};
	
	return 0;
}
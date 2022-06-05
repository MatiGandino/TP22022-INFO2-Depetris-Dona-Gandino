#include <stdio.h>
#include <stdint.h> //para utilizar uint16_t y uint32_t

struct mediciones {
	struct sensores {
		uint16_t valor;
		uint32_t tiempo;
		char indic;
	} humedad, temperatura; 
};

int main() {

	int i = 5;
	struct mediciones med[i];
	
	FILE *fpt;
	fpt = fopen ("ARCHIVO.DAT", "rb");
	
	fread (med, sizeof(struct mediciones), i, fpt);

	
	for (i = 0; i < 5; i++){
	printf ("Sensor: %c \nValor: %d \nTiempo desde la ultima medicion: %d\n\n", med[i].humedad.indic, med[i].humedad.valor, med[i].humedad.tiempo);
	printf ("Sensor: %c \nValor: %d \nTiempo desde la ultima medicion: %d\n\n\n", med[i].temperatura.indic, med[i].temperatura.valor, med[i].temperatura.tiempo);
	};
	
	fclose (fpt);
	
	return 0;
}


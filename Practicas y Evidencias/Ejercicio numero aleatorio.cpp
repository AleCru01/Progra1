#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//ejercicio de generar un numero alateorio y buscar que numero sea
// Declaraciones
long numeroAleatorio(int cadena[], long rango);
int buscarIndice(long numeroX, int arreglo[], int usados[], int cupos);
int yaFueSeleccionado(int indice, int usados[], int cupos);

void sumatoria(int longitud, int ranking[], int cupos, int repechaje){
	long PuntosTotalesRankings = 0;
	int LugaresOcupados[cupos]; // Guardará los índices ya usados
	int i;

	for(i = 0; i < longitud; i++){
		PuntosTotalesRankings += ranking[i];
	}
	printf("Puntos totales de todo el arreglo: %ld\n\n", PuntosTotalesRankings);

	for(i = 0; i < cupos; i++){
		int indice;
		do {
			long numero = numeroAleatorio(ranking, PuntosTotalesRankings);
			printf("Número aleatorio generado: %ld\n", numero);
			indice = buscarIndice(numero, ranking, LugaresOcupados, i);
		} while (yaFueSeleccionado(indice, LugaresOcupados, i));

		LugaresOcupados[i] = indice;
		printf("Índice seleccionado (más cercano): %d\n", indice);
		printf("Valor del ranking en ese índice: %d\n\n", ranking[indice]);

		PuntosTotalesRankings -= ranking[indice];  // Restamos su peso
		ranking[indice] = 0;  // También puedes anularlo directamente
	}
}

// Genera número aleatorio entre 1 y rango
long numeroAleatorio(int cadena[], long rango){
	return 1 + rand() % rango;
}

// Busca el índice cuyo acumulado cruza el número aleatorio
int buscarIndice(long numeroX, int arreglo[], int usados[], int usadosHasta){
	long acumulado = 0;
	for (int i = 0; ; i++) {
		acumulado += arreglo[i];
		if (acumulado >= numeroX)
			return i;
	}
}

// Verifica si el índice ya fue seleccionado
int yaFueSeleccionado(int indice, int usados[], int cupos) {
	for (int i = 0; i < cupos; i++) {
		if (usados[i] == indice)
			return 1; // Ya existe
	}
	return 0;
}

main(){
	int cadena[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	srand(time(NULL)); //semilla
	sumatoria(20, cadena, 5, 1);
}

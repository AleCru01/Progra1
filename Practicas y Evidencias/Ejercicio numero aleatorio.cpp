#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//ejercicio de generar un numero alateorio y buscar que numero sea
long numeroAleatorio(int cadena[], long rango);
int buscarIndice(long numeroX, int arreglo[]);

void sumatoria(int longitud, int ranking[], int cupos, int repechaje){
	long PuntosTotalesRankings = 0;
	int LugaresOcupados[cupos]; //array que nos guarda los indices ya ocupados
	int i;
	for(i = 0; i< longitud; i++){
		PuntosTotalesRankings += ranking[i];
	}
	printf("Puntos totales de todo el arreglo: %d\n\n", PuntosTotalesRankings);
	
	//para obtener los cupos
	for(i = 1; i<=cupos; i++){
		//quiero pasar como parametro el return de numeroAleatorio
		long numero = numeroAleatorio(ranking,PuntosTotalesRankings);
		printf("Numero aleatorio a buscar: %d\n", numero);
		int indice = buscarIndice(numero, ranking); //guardo el indice en el arrary para luego restarlo y que no salga de nuevo
		LugaresOcupados[i-1] = indice;
		printf("El indice que corresponde (el mas cercano) es: %d\n", indice);
		printf("el valor de ese indice es: %d\n\n\n", ranking[indice]);
		
		//ahora hay que restar el valor del ranking y que no salga 
		PuntosTotalesRankings -= LugaresOcupados[i-1];
	}
	
	
}

long numeroAleatorio(int cadena[], long rango){
	int aleatorio =1 + rand() % rango;
	return aleatorio;
}


int buscarIndice(long numeroX, int arreglo[]){
	int i = 0;
	long PuntosAcumulados=arreglo[i];
	do{
		i++;
		PuntosAcumulados+=arreglo[i];
	}while(PuntosAcumulados < numeroX);
	
	//me falta poner alguna condicion de que verifique que el valor de i esta en el array de LugaresOcupados
	//y si esta, volver a generar otro numero aleatorio, y usando recursividad volver a buscar el numero.
	
	
	
	
	//retornara el Indice del arreglo que en donde estara; 
	return i;
}

main(){
	int cadena[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	srand(time(NULL)); //semilla
	sumatoria(20, cadena, 2, 1);
}

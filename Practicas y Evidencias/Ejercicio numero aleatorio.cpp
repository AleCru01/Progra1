#include <stdio.h>

//ejercicio de generar un numero alateorio y buscar que numero sea

void sumatoria(int longitud, int ranking[]){
	int PuntosTotalesRankings = 0;
	int i;
	for(i = 0; i< longitud; i++){
		PuntosTotalesRankings += ranking[i];
	}
	printf("%d", PuntosTotalesRankings);
}

main(){
	int cadena[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	sumatoria(20, cadena);
}

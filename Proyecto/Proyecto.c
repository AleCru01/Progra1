#include <stdio.h>
#include "Recursos/Clasificatorias.h" //Librería propia para hacer las clasificatorias
#include <stdlib.h>
#include <time.h>

int main(){
	printf("oo____oo____oo____oooo____ooooooo___oo______oooooo__________oooo___oo______oo_ooooooo_______ooooo_____ooo_o____ooooo___oooooo__\n");
	printf("oo____oo____oo__oo____oo__oo____oo__oo______oo____oo______oo____oo_oo______oo_oo____oo____oo____oo__oo___oo__oo____oo_oo_______\n");
	printf("oo____oo____oo_oo______oo_oo____oo__oo______oo_____oo____oo________oo______oo_oo____oo__________oo_oo___o_oo_______oo_ooooooo__\n");
	printf("_oo__oooo__oo__oo______oo_ooooooo___oo______oo_____oo____oo________oo______oo_oooooo__________ooo__oo__o__oo_____ooo__oo____oo_\n");
	printf("__oooo__oooo____oo____oo__oo____oo__oo______oo____oo______oo____oo__oo____oo__oo____________ooo_____ooo__oo____ooo____oo____oo_\n");
	printf("___oo____oo_______oooo____oo_____oo_ooooooo_oooooo__________oooo______oooo____oo__________oooooooo___oooo____oooooooo__oooooo__\n");
	printf("_______________________________________________________________________________________________________________________________\n");
	
	srand(time(NULL)); 
	int desicion;
	printf("\n\nQuieres iniciar el mundial? (1.-Si / 2.-NO)  ");
	scanf("%d", &desicion);
	if(desicion == 1){
		InicioClasificacion();
	}else{
		return 1;
	}
}



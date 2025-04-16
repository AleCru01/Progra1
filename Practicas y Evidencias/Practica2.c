#include <stdio.h>

//en esta practica vi que es capaz de leer de un archivo
main(){
	FILE *archivo = fopen("Perez.txt", "r");
	
	if(archivo != NULL){	
		while(feof(archivo) == 0){
			char caracter = fgetc(archivo);
			printf("%c", caracter);
		}
	}
	
}

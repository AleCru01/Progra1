#include <stdio.h>
#include <stdlib.h>

//PRACTICA DE MANEJO DE ARCHIVOS PARA PROYECTO FINAL DE PROGRA 1

//videos: 
/* https://youtu.be/XDmtYJx7t1I */

//https://youtu.be/PPK28h5TmHc

main(){
	
	//fopen() abre el archivo, y se guardara en un apuntador a esa dirección de memoria
	
	/* fopen() tiene 2 parametros ("nombreArchivo", "TipoDeApertura"), El tipo de apertura son los sig:
		-r = read
		-w = write
		-b = binary
		
	funciones que podríamos usar : 
		-feof() -> Find End Of File, BUSCA EL FIN DEL ARCHIVO
		-fgetc() -> se utiliza para leer el siguiente carácter de un flujo de entrada, avanzando el indicador de posición para el flujo.
	
	*/
	
	//Ejemplo de lectura caracter por caracter: 
	
	FILE *archivo = fopen("Juan.txt", "rb");

	if(archivo == NULL){
		perror("Error en la apertura del archivo");
		return 1;
	}else{
		char caracter;
		
		int valor;
		char cadena[4];
		while(feof(archivo) == 0){
			/*
			caracter = fgetc(archivo);
			printf("%c", caracter);
			*/
			fscanf(archivo,"%d%s", &valor, &cadena);
			printf("%d %s\n", valor, cadena);
		}
		
		printf("\n\nEl archivo se leyo correctamente: ");
	}
	
	//EJEMPLO DE LECTURA POR 2 VARIABLES
	//vamos a leer el archivo e irla guardando en una cadena de caracteres y en una variable de numeros
/*
	int valor;
	char cadena[4];
	while(feof(archivo) == 0){
		fscanf(archivo,"%d%s", &valor, &cadena);
		printf("%d %s\n", valor, cadena);
	}
		
	printf("\n\nEl archivo se leyo correctamente: ");
*/	
	fclose(archivo);//cerrar archivo
}



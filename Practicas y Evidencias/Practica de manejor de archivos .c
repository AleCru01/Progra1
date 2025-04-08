#include <stdio.h>
#include <stdlib.h>

//PRACTICA DE MANEJO DE ARCHIVOS PARA PROYECTO FINAL DE PROGRA 1

//video: 
/* https://youtu.be/XDmtYJx7t1I */

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
	
	FILE * archivo = fopen("practica.txt", "rb");
	if(archivo == NULL){
		perror("Error en la apertura del archivo");
		return 1;
	}else{
		char caracter;
		
		while(feof(archivo) == 0){
			caracter = fgetc(archivo);
			printf("%c", caracter);
		}
		
		fclose(archivo);//cerrar archivo
		printf("\nEl archivo se leyo correctamente: ");
	}
}



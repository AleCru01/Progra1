#include <stdio.h>

void prueba(FILE *juan){
	fprintf(juan, "1ra Escritura");
	fprintf(juan, "\nHOLA AMIGOS");
}

void prueba2(FILE *pepe){
	fprintf(pepe, "\n2nda escritura desde otra funcion");
	fprintf(pepe, "\nJuan Perez");
}
main(){
	FILE *archivo = fopen("Archivo.txt", "w");
	
	prueba(archivo);
	prueba2(archivo);
}

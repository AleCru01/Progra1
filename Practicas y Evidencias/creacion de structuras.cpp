//ejercicio de creacion de estructuras


#include <stdio.h>
#include <stdlib.h> //libreria para definir la funcion Exit(1) y terminar el programa
#include <time.h>
#include <string.h>

//leer datos
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad) {
    char buffer[100];
    int contador = 0;
    
    while (fgets(buffer, sizeof(buffer), confederacion) != NULL) contador++;
    rewind(confederacion);
    
    *nombres = (char **)malloc(contador * sizeof(char *));
    *rankings = (int *)malloc(contador * sizeof(int));
    
    int i; 
    for (i = 0; i < contador; i++) {
        fgets(buffer, sizeof(buffer), confederacion);
        buffer[strcspn(buffer, "\n")] = '\0';
        (*nombres)[i] = strdup(strtok(buffer, " "));
        (*rankings)[i] = atoi(strtok(NULL, " "));
    }
    *cantidad = contador;
}

//structura

struct Grupos{
	int idGrupo;
	char **nombres;
	int *rankings;
	int *puntos;
};

main(){
	struct Grupos totales[12]; //hago un struct de array 12
	
	//abrimos el archivo:
	FILE *paises = fopen("UEFA", "r");
	if(!paises){
		printf("no lo encuentro w");
	}
}

/*
	Aqui va a hacer una libreria GENERAL para cualquier archivo del programa, podria contener las siguientes funciones. 
	
	-SimuladorPartidos()
	-probabilidad()
	-etc
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaracion de funciones
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad);



void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad) {
    char buffer[100];
    int contador = 0;
    
    // Contar líneas (países) en el archivo
    while (fgets(buffer, sizeof(buffer), confederacion) != NULL) contador++;
    rewind(confederacion);
    
    // Reservar memoria
    *nombres = (char **)malloc(contador * sizeof(char *));
    *rankings = (int *)malloc(contador * sizeof(int));
    
    // Leer y almacenar datos
    int i; 
    for (i = 0; i < contador; i++) {
        fgets(buffer, sizeof(buffer), confederacion);
        buffer[strcspn(buffer, "\n")] = '\0';
        (*nombres)[i] = strdup(strtok(buffer, " "));
        (*rankings)[i] = atoi(strtok(NULL, " "));
    }
    *cantidad = contador;
}

void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad) {
	int i; 
    for (i = 0; i < cantidad; i++) free(nombres[i]);
    free(nombres);
    free(rankings);
}

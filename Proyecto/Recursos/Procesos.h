/*
	Aqui va a hacer una libreria GENERAL para cualquier archivo del programa, podria contener las siguientes funciones. 
	
	-SimuladorPartidos()
	-probabilidad()
	-etc
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//declaracion de funciones
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad);
void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
int sacarUnSelec(int rango, int array[], int cantidad,int Salidos[], int cupos);

//INICIO DE PROCESOS

void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad) {
    char buffer[100];
    int contador = 0;
    
    // Contar lÃ­neas (paÃ­ses) en el archivo
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


int sacarUnSelec(int rango, int array[], int cantidad, int Salidos[], int cupos){
	long numero = 1 + rand() % rango;
	
	//vamos a buscarlo en el array
	long acumulado = 0;
	int i = 0;
	int indice = 0;
	do{
		indice++; 
		acumulado +=array[indice];
	}while(acumulado <= numero);
	
	//si ya esta en los salidos, por mediode recursividad se volvera a ejecutar
	//al parcer esto no funciona, hy que ver que pedo 
	for(i = 0; i<cupos; i++){
		if(indice == Salidos[cupos]){
			sacarUnSelec(rango,array,cantidad,Salidos,cupos);
		}
	}
	
	return indice;
}

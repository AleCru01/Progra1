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

// ----------------------------
// ESTRUCTURA NUEVA AÑADIDA
// ----------------------------
typedef struct {
    char nombre[50];  // Nombre del equipo
    int ranking_fifa; // Ranking FIFA
} Equipo;

// ----------------------------
// DECLARACIONES ORIGINALES (se mantienen)
// ----------------------------
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad);
void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
int sacarUnSelec(int rango, int array[], int cantidad,int Salidos[], int cupos, int repe[],int CuposPlayoff);

// ----------------------------
// FUNCIONES NUEVAS AÑADIDAS
// ----------------------------
void cargarEquiposArray(FILE *archivo, Equipo **arrayEquipos, int *total) {
    char buffer[100];
    int contador = 0;
    
    // Contar líneas en archivo
    while (fgets(buffer, sizeof(buffer), archivo)) contador++;
    rewind(archivo);
    
    // Crear array de estructuras
    *arrayEquipos = (Equipo*)malloc(contador * sizeof(Equipo));
    
    // Leer datos
    int i;
    for (i = 0; i < contador; i++) {
        fgets(buffer, sizeof(buffer), archivo);
        buffer[strcspn(buffer, "\n")] = '\0';
        sscanf(buffer, "%49s %d", (*arrayEquipos)[i].nombre, &(*arrayEquipos)[i].ranking_fifa);
    }
    *total = contador;
}

void mostrarArrayEquipos(Equipo *array, int total) {
    printf("\n--- EQUIPOS EN ARRAY DE STRUCT ---\n");
    int i;
    for (i = 0; i < total; i++) {
        printf("%-20s (Rank: %d)\n", array[i].nombre, array[i].ranking_fifa);
    }
}

// ----------------------------
// FUNCIONES ORIGINALES (se mantienen exactamente igual)
// ----------------------------
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

void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad) {
    int i; 
    for (i = 0; i < cantidad; i++) free(nombres[i]);
    free(nombres);
    free(rankings);
}
//(rango = sumatoia, array = array de todos los rankings, cantidad = no. de paises, Salidos = array de los que ya salieron, cupos = cupos, repe[] = array de los repechaje, CuposPlayoffs = los cupos para play offs
int sacarUnSelec(int rango, int array[], int cantidad, int Salidos[], int cupos, int repe[], int CuposPlayoff){
    long numero = 1 + rand() % rango;
    
    long acumulado = 0;
    int i = 0;
    int indice = 0;
    do{
        indice++; 
        acumulado +=array[indice];
    }while(acumulado <= numero);
    
    for(i = 0; i<=cupos; i++){
        if(indice == Salidos[i]){
            return sacarUnSelec(rango,array,cantidad,Salidos,cupos,repe, CuposPlayoff);
        }
        
    }
    for (i = 0; i < CuposPlayoff; i++) {
  	  if (indice == repe[i]) {
		return sacarUnSelec(rango,array,cantidad,Salidos,cupos,repe, CuposPlayoff);
  	  }
	}	
    return indice;
}

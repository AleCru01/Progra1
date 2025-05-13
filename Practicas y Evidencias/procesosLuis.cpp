/*
	Aqui va a hacer una libreria GENERAL para cualquier archivo del programa, podria contener las siguientes funciones. 
	
	-SimuladorPartidos()
	-probabilidad()
	-etc


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaracion de funciones
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad);
void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void sumatoria();

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


void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad){
	//la neta no jalo w, no sé pq 
	int contador = 0, i;
    char buffer[100];
    // Contar lÃ­neas (paÃ­ses) en el archivo
    while (fgets(buffer, sizeof(buffer), confederacion) != NULL) contador++;
    rewind(confederacion);
    
    for(i = 0; i< contador; i++){
    	fscanf(confederacion, "%s %d", &nombres[i], &rankings[i]);
	}
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////
//////////////////////
////////////////////
///////////////
////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración de funciones
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad);
void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
int sumatoria(int *rankings, int cantidad);  // Función sumatoria actualizada

void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad) {
    if (confederacion == NULL) {
        fprintf(stderr, "Error: Archivo no válido\n");
        *cantidad = 0;
        return;
    }

    char buffer[100];
    int contador = 0;
    
    // Contar líneas (países) en el archivo
    while (fgets(buffer, sizeof(buffer), confederacion) != NULL) {
        contador++;
    }
    rewind(confederacion);
    
    // Reservar memoria
    *nombres = (char **)malloc(contador * sizeof(char *));
    *rankings = (int *)malloc(contador * sizeof(int));
    
    if (*nombres == NULL || *rankings == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria\n");
        if (*nombres) free(*nombres);
        if (*rankings) free(*rankings);
        *cantidad = 0;
        return 0;
    }
    
    // Leer y almacenar datos
    for (int i = 0; i < contador; i++) {
        if (fgets(buffer, sizeof(buffer), confederacion) == NULL) break;
        
        buffer[strcspn(buffer, "\n")] = '\0';
        char *nombre = strtok(buffer, " ");
        char *ranking_str = strtok(NULL, " ");
        
        if (nombre == NULL || ranking_str == NULL) {
            fprintf(stderr, "Error: Formato de archivo incorrecto en línea %d\n", i+1);
            continue;
        }
        
        (*nombres)[i] = strdup(nombre);
        (*rankings)[i] = atoi(ranking_str);
        
        if ((*nombres)[i] == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria para el nombre\n");
        }
    }
    *cantidad = contador;
}

void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad) {
    if (nombres != NULL) {
        for (int i = 0; i < cantidad; i++) {
            if (nombres[i] != NULL) {
                free(nombres[i]);
            }
        }
        free(nombres);
    }
    
    if (rankings != NULL) {
        free(rankings);
    }
}

void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad) {
    if (confederacion == NULL) {
        fprintf(stderr, "Error: Archivo no válido\n");
        *cantidad = 0;
        return;
    }

    char buffer[100];
    int contador = 0;
    
    // Contar líneas (países) en el archivo
    while (fgets(buffer, sizeof(buffer), confederacion) != NULL) {
        contador++;
    }
    rewind(confederacion);
    
    // Reservar memoria
    *nombres = (char **)malloc(contador * sizeof(char *));
    *rankings = (int *)malloc(contador * sizeof(int));
    
    if (*nombres == NULL || *rankings == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria\n");
        if (*nombres) free(*nombres);
        if (*rankings) free(*rankings);
        *cantidad = 0;
        return;
    }
    
    // Leer datos usando fscanf
    for (int i = 0; i < contador; i++) {
        char nombre_temp[100];
        int ranking_temp;
        
        if (fscanf(confederacion, "%99s %d", nombre_temp, &ranking_temp) != 2) {
            fprintf(stderr, "Error: Formato de archivo incorrecto en línea %d\n", i+1);
            (*nombres)[i] = NULL;
            (*rankings)[i] = 0;
            continue;
        }
        
        (*nombres)[i] = strdup(nombre_temp);
        (*rankings)[i] = ranking_temp;
        
        if ((*nombres)[i] == NULL) {
            fprintf(stderr, "Error: No se pudo asignar memoria para el nombre\n");
        }
    }
    *cantidad = contador;
}

// Función sumatoria mejorada
int sumatoria(int *rankings, int cantidad) {
    if (rankings == NULL || cantidad <= 0) {
        fprintf(stderr, "Error: Datos no válidos para sumatoria\n");
        return 0;
    }

    int total = 0;
    for (int i = 0; i < cantidad; i++) {
        total += rankings[i];
    }

    return total;
}

// Ejemplo de uso
int main() {
    FILE *archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char **nombres;
    int *rankings;
    int cantidad;

    // Obtener datos
    obtenerDatosConfederacion(archivo, &nombres, &rankings, &cantidad);
    fclose(archivo);

    if (cantidad > 0) {
        // Calcular sumatoria
        int total = sumatoria(rankings, cantidad);
        printf("Sumatoria de rankings: %d\n", total);

        // Liberar memoria
        liberarDatosConfederacion(nombres, rankings, cantidad);
    }

    return 0;
}

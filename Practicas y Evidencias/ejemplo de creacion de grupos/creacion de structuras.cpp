#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int sacarUnNumero(int usados[]) {
    int num;

    do {
        num = rand() % 48;
    } while (usados[num]); // si ya fue usado, sigue buscando

    usados[num] = 1; // marcar como usado
    return num;
}

struct Grupo {
	//ponemos 4 pq son 4 equipos alv
    int idGrupo;
    char *nombres[4];
    int rankings[4];
    int puntos[4];
};

void imprimirGrupos(struct Grupo grupos[]) {
    for (int i = 0; i < 12; i++) {
        printf("\nGrupo %c\n", 'A' + i);
        for (int j = 0; j < 4; j++) {
            printf("  %s - %d puntos (ranking: %d)\n",
                   grupos[i].nombres[j],
                   grupos[i].puntos[j],
                   grupos[i].rankings[j]);
        }
    }
}

int main() {
    struct Grupo grupos[12];
    FILE *archivo = fopen("UEFA.txt", "r");
    //Obtener datos: 
    char **nombres;
    int *rankings;
    int cantidad = 0;
    int i, j;
    obtenerDatosConfederacion(archivo, &nombres, &rankings, &cantidad);
    
    int usados[48] = {0};  // inicializar todos en 0

	for(i = 0; i < 12; i++) {
	    for(j = 0; j < 4; j++) {
	        int num = sacarUnNumero(usados);
	        grupos[i].nombres[j] = strdup(nombres[num]); 
	        grupos[i].rankings[j] = rankings[num]; 
	        grupos[i].puntos[j] = 0;
	    }
	}
    
    imprimirGrupos(grupos);

    // Liberar memoria usada para nombres
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 4; j++) {
            free(grupos[i].nombres[j]);
        }
    }
	 for (i = 0; i < cantidad; i++) free(nombres[i]);
    free(nombres);
    free(rankings);
    return 0;
}


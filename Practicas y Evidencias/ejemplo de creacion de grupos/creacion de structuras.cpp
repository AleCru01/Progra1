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


struct Grupo {
	//ponemos 4 pq son 4 equipos alv
    int idGrupo;
    char *nombres[4];
    int rankings[4];
    int puntos[4];
};

void crearGrupos(struct Grupo grupos[], const char *archivo) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("Error al abrir el archivo %s\n", archivo);
        exit(1);
    }

    char buffer[100];
    int grupoActual = 0;
    int posicion = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

        buffer[strcspn(buffer, "\n")] = '\0'; // quitar el salto de línea
        char *nombre = strtok(buffer, " ");
        char *rankingStr = strtok(NULL, " ");

        grupos[grupoActual].nombres[posicion] = strdup(nombre);
        grupos[grupoActual].rankings[posicion] = atoi(rankingStr);
        grupos[grupoActual].puntos[posicion] = 0;

        posicion++;

        if (posicion == 4) {
            grupos[grupoActual].idGrupo = grupoActual + 1;
            grupoActual++;
            posicion = 0;
        }
    }

    fclose(fp);
}

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
    int **ranking;
    int cantidad = 0;
    obtenerDatosConfederacion(archivo, &nombres, &rankings, &cantidad);
    
    crearGrupos(grupos, "UEFA.txt");
    imprimirGrupos(grupos);

    // Liberar memoria usada para nombres
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 4; j++) {
            free(grupos[i].nombres[j]);
        }
    }

    return 0;
}


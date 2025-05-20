#include "Procesos.h" //Librer�a general para TODOS los procesos comunes 

//creacion de structura de grupos
struct Grupo {
	//ponemos 4 pq son 4 equipos alv
    int idGrupo;
    char *nombres[4];
    int rankings[4];
    int puntos[4];
};

//variable para sacar un numero aleatorio de 1 a 48
int sacarUnNumero(int usados[]) {
    int num;

    do {
        num = rand() % 48;
    } while (usados[num]); // si ya fue usado, sigue buscando

    usados[num] = 1; // marcar como usado
    return num;
}

//impresion
void imprimirGrupos(struct Grupo grupos[]) {
	int i, j;
    for (i = 0; i < 12; i++) {
        printf("\nGrupo %c\n", 'A' + i);
        for (j = 0; j < 4; j++) {
            printf("  %s - %d puntos (ranking: %d)\n",
                   grupos[i].nombres[j],
                   grupos[i].puntos[j],
                   grupos[i].rankings[j]);
        }
    }
}

//inicio de todo
void crearGrupos(){
	struct Grupo grupos[12];
    FILE *archivo = fopen("Recursos/PaisesFinales.txt.txt", "r");
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
    for (i = 0; i < 12; i++) {
        for(j = 0; j < 4; j++) {
            free(grupos[i].nombres[j]);
        }
    }
	 for (i = 0; i < cantidad; i++) free(nombres[i]);
    free(nombres);
    free(rankings);
}

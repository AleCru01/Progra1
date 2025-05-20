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
int ElegirUltimosLugares(int *rankings, int Salidos[], int cantidad);

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
    //sacamos un numero aleatorio y un acoumulado
    long acumulado = 0;
    int i = 0;
    //variable de 
    int indice = -1;
    do{
        indice++; 
        acumulado +=array[indice];
    }while(acumulado <= numero);
    
    for(i = 0; i<cupos; i++){
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
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Función para calcular probabilidad de empate
float probabilidad_empate(int ranking1, int ranking2) {
    if (ranking1 <= 0 || ranking2 <= 0) return 0.0f; // Evitar división por cero
    int menor = (ranking1 < ranking2) ? ranking1 : ranking2;
    return (float)menor / ((ranking1 > ranking2) ? ranking1 : ranking2);
}

// Función para simular partido
void partido(Equipo local, Equipo visitante) {
    srand(time(NULL));
    float prob_empate = probabilidad_empate(local.ranking_fifa, visitante.ranking_fifa);
    float prob_local = (1.0f - prob_empate) * (visitante.ranking_fifa / (float)(local.ranking_fifa + visitante.ranking_fifa));
    float prob_visitante = 1.0f - prob_empate - prob_local;

    float resultado = (float)rand() / RAND_MAX;

    printf("\n--- SIMULACIÓN ---\n");
    printf("%s (%d) vs %s (%d)\n", local.nombre, local.ranking_fifa, visitante.nombre, visitante.ranking_fifa);
    printf("Probabilidades:\n");
    printf("- Victoria %s: %.2f%%\n", local.nombre, prob_local * 100);
    printf("- Empate: %.2f%%\n", prob_empate * 100);
    printf("- Victoria %s: %.2f%%\n", visitante.nombre, prob_visitante * 100);

    if (resultado < prob_local) {
        printf("\nResultado: Gana %s\n", local.nombre);
    } else if (resultado < prob_local + prob_empate) {
        printf("\nResultado: Empate\n");
    } else {
        printf("\nResultado: Gana %s\n", visitante.nombre);
    }
}

int ElegirUltimosLugares(int *rankings, int Salidos[], int cantidad){
	int numero = 1 + rand() % 6;
	
	if(numero == Salidos[0] || numero == Salidos[1]){
		return ElegirUltimosLugares(rankings, Salidos, cantidad);
	}else{
		return numero;
	}
}

/*
// Función original para cargar datos desde archivo
void cargarEquiposArray(FILE *archivo, Equipo **arrayEquipos, int *total) {
    char buffer[100];
    int contador = 0;
    while (fgets(buffer, sizeof(buffer), archivo)) contador++;
    rewind(archivo);
    *arrayEquipos = (Equipo*)malloc(contador * sizeof(Equipo));
    int i;
    for (i = 0; i < contador; i++) {
        fgets(buffer, sizeof(buffer), archivo);
        buffer[strcspn(buffer, "\n")] = '\0';
        sscanf(buffer, "%49s %d", (*arrayEquipos)[i].nombre, &(*arrayEquipos)[i].ranking_fifa);
    }
    *total = contador;
}
*/
/* Ejemplo de uso integrado
int main() {
    FILE *archivo = fopen("equipos.txt", "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return 1;
    }

    Equipo *equipos;
    int totalEquipos;
    cargarEquiposArray(archivo, &equipos, &totalEquipos);
    fclose(archivo);

    // Simular un partido entre el primer y segundo equipo del archivo
    if (totalEquipos >= 2) {
        partido(equipos[0], equipos[1]);
    }

    free(equipos);
    return 0;
}

}*/

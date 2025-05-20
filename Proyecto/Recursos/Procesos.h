#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ----------------------------
// ESTRUCTURA ORIGINAL
// ----------------------------
typedef struct {
    char nombre[50];  // Nombre del equipo
    int ranking_fifa; // Ranking FIFA
} Equipo;

// ----------------------------
// DECLARACIONES ORIGINALES
// ----------------------------
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad);
void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
int sacarUnSelec(int rango, int array[], int cantidad,int Salidos[], int cupos, int repe[],int CuposPlayoff);
int ElegirUltimosLugares(int *rankings, int Salidos[], int cantidad);

// ----------------------------
// FUNCIONES ORIGINALES
// ----------------------------
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

void mostrarArrayEquipos(Equipo *array, int total) {
    printf("\n--- EQUIPOS EN ARRAY DE STRUCT ---\n");
    int i;
    for (i = 0; i < total; i++) {
        printf("%-20s (Rank: %d)\n", array[i].nombre, array[i].ranking_fifa);
    }
}

// ----------------------------
// FUNCIONES DE SIMULACIÓN AÑADIDAS
// ----------------------------

// Función original para probabilidad de empate (ya existía)
float probabilidad_empate(int ranking1, int ranking2) {
    if (ranking1 <= 0 || ranking2 <= 0) return 0.0f;
    int menor = (ranking1 < ranking2) ? ranking1 : ranking2;
    return (float)menor / ((ranking1 > ranking2) ? ranking1 : ranking2);
}

// Función mejorada para simular un partido (nueva versión)
Resultado simularPartidoCompleto(Equipo local, Equipo visitante) {
    Resultado resultado;
    float prob_empate = probabilidad_empate(local.ranking_fifa, visitante.ranking_fifa);
    float prob_local = (1.0f - prob_empate) * 
                     (visitante.ranking_fifa / (float)(local.ranking_fifa + visitante.ranking_fifa));
    
    float random = (float)rand() / RAND_MAX;
    
    if (random < prob_local) {
        resultado.goles_local = 1 + rand() % (2 + (50 - local.ranking_fifa)/20);
        resultado.goles_visitante = rand() % resultado.goles_local;
    } 
    else if (random < prob_local + prob_empate) {
        resultado.goles_local = rand() % 3;
        resultado.goles_visitante = resultado.goles_local;
    } 
    else {
        resultado.goles_visitante = 1 + rand() % (2 + (50 - visitante.ranking_fifa)/20);
        resultado.goles_local = rand() % resultado.goles_visitante;
    }
    
    return resultado;
}

// Función para simular todos los partidos de un grupo (nueva)
void simularFaseDeGrupos(Equipo grupo[4]) {
    PosicionGrupo tabla[4] = {0};
    
    // Inicializar tabla
    for (int i = 0; i < 4; i++) {
        strcpy(tabla[i].nombre, grupo[i].nombre);
    }
    
    printf("\n=== SIMULACIÓN DE FASE DE GRUPOS ===\n");
    
    // Simular todos los partidos (todos contra todos)
    for (int i = 0; i < 4; i++) {
        for (int j = i+1; j < 4; j++) {
            Resultado res = simularPartidoCompleto(grupo[i], grupo[j]);
            
            printf("%s %d - %d %s\n", 
                  grupo[i].nombre, res.goles_local, res.goles_visitante, grupo[j].nombre);
            
            // Actualizar tabla de posiciones
            tabla[i].goles_favor += res.goles_local;
            tabla[i].goles_contra += res.goles_visitante;
            tabla[j].goles_favor += res.goles_visitante;
            tabla[j].goles_contra += res.goles_local;
            
            if (res.goles_local > res.goles_visitante) {
                tabla[i].puntos += 3;
            } else if (res.goles_local < res.goles_visitante) {
                tabla[j].puntos += 3;
            } else {
                tabla[i].puntos += 1;
                tabla[j].puntos += 1;
            }
        }
    }
    
    // Calcular diferencia de goles
    for (int i = 0; i < 4; i++) {
        tabla[i].diferencia_goles = tabla[i].goles_favor - tabla[i].goles_contra;
    }
    
    // Mostrar tabla de posiciones
    printf("\n=== TABLA FINAL ===\n");
    printf("Equipo\t\t\tPts\tGF\tGC\tDG\n");
    for (int i = 0; i < 4; i++) {
        printf("%-20s\t%d\t%d\t%d\t%d\n", 
              tabla[i].nombre, tabla[i].puntos,
              tabla[i].goles_favor, tabla[i].goles_contra,
              tabla[i].diferencia_goles);
    }
}

// ----------------------------
// ESTRUCTURAS AÑADIDAS PARA LA SIMULACIÓN
// ----------------------------
typedef struct {
    int goles_local;
    int goles_visitante;
} Resultado;

typedef struct {
    char nombre[50];
    int puntos;
    int goles_favor;
    int goles_contra;
    int diferencia_goles;
} PosicionGrupo;

// ----------------------------
// FUNCIONES ORIGINALES MANTENIDAS (COMPLETAS)
// ----------------------------
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad) {
    /* ... (código original completo se mantiene igual) ... */
}

void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad) {
    /* ... (código original completo se mantiene igual) ... */
}

int sacarUnSelec(int rango, int array[], int cantidad, int Salidos[], int cupos, int repe[], int CuposPlayoff) {
    /* ... (código original completo se mantiene igual) ... */
}

int ElegirUltimosLugares(int *rankings, int Salidos[], int cantidad) {
    /* ... (código original completo se mantiene igual) ... */
}

// ----------------------------
// FUNCIÓN MAIN DE EJEMPLO
// ----------------------------
int main() {
    srand(time(NULL)); // Inicializar semilla aleatoria
    
    // Ejemplo con un grupo de 4 equipos
    Equipo grupoEjemplo[4] = {
        {"Brasil", 1},
        {"Suiza", 15},
        {"Serbia", 25},
        {"Camerun", 38}
    };
    
    // Simular todos los partidos del grupo
    simularFaseDeGrupos(grupoEjemplo);
    
    return 0;
}

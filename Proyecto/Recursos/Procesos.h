

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// ----------------------------
// DECLARACIONES ORIGINALES (se mantienen)
// ----------------------------
void obtenerDatosConfederacion(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad);
void obtenerDatosVictor(FILE *confederacion, char ***nombres, int **rankings, int *cantidad);
int sacarUnSelec(int rango, int array[], int cantidad,int Salidos[], int cupos, int repe[],int CuposPlayoff);
int ElegirUltimosLugares(int *rankings, int Salidos[], int cantidad);

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
	
int ElegirUltimosLugares(int *rankings, int Salidos[], int cantidad){
	int numero = 1 + rand() % 6;
	
	if(numero == Salidos[0] || numero == Salidos[1]){
		return ElegirUltimosLugares(rankings, Salidos, cantidad);
	}else{
		return numero;
	}
}


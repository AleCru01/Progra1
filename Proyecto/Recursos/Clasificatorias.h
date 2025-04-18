#include <stdio.h>
#include <stdlib.h> //librería para definir la función Exit(1) y terminar el programa

void definirCupos();
void clasificacion(FILE *confederacion, int cupos, int playoffs);
//defini el archivo donde voy a guardar todos los datos, como GLOBAL 
FILE *PaisesCla;


//proceso de abrir los documentos:
void InicioClasificacion(){
	//proceso de leer los archivos .txt donde estan la lista de los paises y su ranking fifa
	FILE *CONCA = fopen("Recursos/Confederacion/CONCACAF.txt", "r"); //america del norte
	FILE *UEFA = fopen("Recursos/Confederacion/UEFA.txt", "r"); //Europa
	FILE *CONME = fopen("Recursos/Confederacion/CONMEBOL.txt", "r"); //Sudamerica
	FILE *AFC = fopen("Recursos/Confederacion/AFC.txt", "r"); //Asia 
	FILE *CAF = fopen("Recursos/Confederacion/CAF.txt", "r"); //Africa
	FILE *OFC = fopen("Recursos/Confederacion/OFC.txt", "r"); //Oceania
	
	PaisesCla = fopen("Recursos/PaisesFinales.txt", "w");
	
	// Verificar si alguno no se abrió
	
	/*
		FICHA TÉCNICA: 
			Use condicionales NEGATIVAS para verificar si algun documento no existe
			basicamente: 
			!CAF  -> es lo mismo a -> CAF == NULL
	*/
	if (!CONCA) { printf("ARCHIVO FALTANTE: CONCACAF.txt\n\n"); exit(1); }
    if (!UEFA)  { printf("ARCHIVO FALTANTE: UEFA.txt\n\n");      exit(1); }
    if (!CONME) { printf("ARCHIVO FALTANTE: CONMEBOL.txt\n\n");  exit(1); }
    if (!AFC)   { printf("ARCHIVO FALTANTE: AFC.txt\n\n");       exit(1); }
    if (!CAF)   { printf("ARCHIVO FALTANTE: CAF.txt\n\n");       exit(1); }
    if (!OFC)   { printf("ARCHIVO FALTANTE: OFC.txt\n\n");       exit(1); }
	
	
	//es un array con las direcciones de memoria de los 6 archivos para pasarlo de parametro
	FILE *confederaciones[6] = {CONCA, UEFA, CONME, AFC,CAF, OFC};	
	
	/*tanto los cupos seguros y los playoffs se van a pasar
	  como parametros en una funcions y aparte, estan acomodados
	  como van en el arreglo *confederaciones
	*/
	int cuposSeguros[6] = {3,16,6,8,9,1}; 
	int playoff[6] = {2,0,1,1,1,1};
	int i;
	for(i = 0; i<6; i++){
		clasificacion(confederaciones[i], cuposSeguros[i], playoff[i]);
	}
	// cerrar los archivos al final:
    fclose(CONCA);
    fclose(UEFA);
    fclose(CONME);
    fclose(AFC);
    fclose(CAF);
    fclose(OFC);
    fclose(PaisesCla);
}


void clasificacion(FILE *confederacion, int cupos, int playoffs){
	if(cupos == 3){
		//esta condición fue hecha para detectar si te estan pasando como parametro
		//a la CONCACAF y agregarle directamente a los anfitriones, quería comparar 
		//los punteros FILE *confederación con FILE *CONCA pero tendría que pasarlo
		//como parametro y ne, mjr este 3 porque igual CONCA solo tiene 3 cupos directos
		
		fprintf(PaisesCla, "Estados Unidos 1649\nMexico 1647\nCanadá 1532");
	}
	
	//aquí debo poner una función que pueda leerme todos los paises en un array
	//Prueba ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    for (int i = 0; i < contador; i++) {
        fgets(buffer, sizeof(buffer), confederacion);
        buffer[strcspn(buffer, "\n")] = '\0';
        (*nombres)[i] = strdup(strtok(buffer, " "));
        (*rankings)[i] = atoi(strtok(NULL, " "));
    }
    *cantidad = contador;
}

void liberarDatosConfederacion(char **nombres, int *rankings, int cantidad) {
    for (int i = 0; i < cantidad; i++) free(nombres[i]);
    free(nombres);
    free(rankings);
}
	
}

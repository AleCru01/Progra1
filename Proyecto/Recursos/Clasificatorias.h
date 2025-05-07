#include <stdio.h>
#include <stdlib.h> //libreria para definir la funcion Exit(1) y terminar el programa
#include "Procesos.h" //Librería general para TODOS los procesos comunes 

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
	
	// Verificar si alguno no se abria
	
	/*
		FICHA TECNICA: 
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
	
	/*
	  tanto los cupos seguros y los playoffs se van a pasar
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
		//esta condicion fue hecha para detectar si te estan pasando como parametro
		//a la CONCACAF y agregarle directamente a los anfitriones, queria comparar 
		//los punteros FILE *confederacion con FILE *CONCA pero tendria que pasarlo
		//como parametro y ne, mjr este 3 porque igual CONCA solo tiene 3 cupos directos
		
		fprintf(PaisesCla, "Estados Unidos 1649\nMexico 1647\nCanada 1532");
	}
	
	char **nombres = NULL;
	int *rankings = NULL;
	int cantidad = 0;
	
	obtenerDatosVictor(confederacion, &nombres, &rankings, &cantidad);
	
	printf("Paises y Rankings \n\n");
	int i;
	for(i = 0; i<cantidad; i++){
		printf("%s - %d \n", nombres[i], rankings[i]);
	}
	
	
}

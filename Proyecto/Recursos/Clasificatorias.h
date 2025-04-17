#include <stdio.h>
#include <stdlib.h> //librería para definir la función Exit(1) y terminar el programa


//proceso de abrir los documentos:
void InicioClasificacion(){
	//proceso de leer los archivos .txt donde estan la lista de los paises y su ranking fifa
	FILE *CONCA = fopen("Recursos/Confederacion/CONCACAF.txt", "r"); //america del norte
	FILE *UEFA = fopen("Recursos/Confederacion/UEFA.txt", "r"); //Europa
	FILE *CONME = fopen("Recursos/Confederacion/CONMEBOL.txt", "r"); //Sudamerica
	FILE *AFC = fopen("Recursos/Confederacion/AFC.txt", "r"); //Asia 
	FILE *CAF = fopen("Recursos/Confederacion/CAF.txt", "r"); //Africa
	FILE *OFC = fopen("Recursos/Confederacion/OFC.txt", "r"); //Oceania
	
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
	
	
	int confederaciones[6] = {*CONCA, *UEFA, *CONME, *AFC,*CAF, *OFC};	
	
	
	// cerrar los archivos al final:
    fclose(CONCA);
    fclose(UEFA);
    fclose(CONME);
    fclose(AFC);
    fclose(CAF);
    fclose(OFC);
}

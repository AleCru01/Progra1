#include <stdio.h>
#include <stdlib.h> //librer�a para definir la funci�n Exit(1) y terminar el programa

void clasificacion(FILE *confederacion, int cupos, int playoffs);

//proceso de abrir los documentos:
void InicioClasificacion(){
	//proceso de leer los archivos .txt donde estan la lista de los paises y su ranking fifa
	FILE *CONCA = fopen("Recursos/Confederacion/CONCACAF.txt", "r"); //america del norte
	FILE *UEFA = fopen("Recursos/Confederacion/UEFA.txt", "r"); //Europa
	FILE *CONME = fopen("Recursos/Confederacion/CONMEBOL.txt", "r"); //Sudamerica
	FILE *AFC = fopen("Recursos/Confederacion/AFC.txt", "r"); //Asia 
	FILE *CAF = fopen("Recursos/Confederacion/CAF.txt", "r"); //Africa
	FILE *OFC = fopen("Recursos/Confederacion/OFC.txt", "r"); //Oceania
	
	FILE *PaisesCla = fopen("Recursos/PaisesFinales.txt", "w");
	
	// Verificar si alguno no se abri�
	
	/*
		FICHA T�CNICA: 
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
		//esta condici�n fue hecha para detectar si te estan pasando como parametro
		//a la CONCACAF y agregarle directamente a los anfitriones, quer�a comparar 
		//los punteros FILE *confederaci�n con FILE *CONCA pero tendr�a que pasarlo
		//como parametro y ne, mjr este 3 porque igual CONCA solo tiene 3 cupos directos
		
		fprintf(PaisesCla, "Estados Unidos 1649\nM�xico 1647\nCanad� 1532");
	}
}

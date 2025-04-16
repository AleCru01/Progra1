#include <stdio.h>

//proceso de abrir los documentos:
void InicioClasificacion(){
	//proceso de leer los archivos .txt donde estan la lista de los paises y su ranking fifa
	FILE *CONCA = fopen("Recursos/Confederacion/CONCACAF.txt", "r"); //america del norte
	FILE *UEFA = fopen("Recursos/Confederacion/UEFA.txt", "r"); //Europa
	FILE *CONME = fopen("Recursos/Confederacion/CONMEBOL.txt", "r"); //Sudamerica
	FILE *AFC = fopen("Recursos/Confederacion/AFC.txt", "r"); //Asia 
	
	
	//NOTIFICACIÓN DE QUE FALTA UN ARCHIVO EN ESPECIFICO
	if(CONCA == NULL){
		printf("ARCHIVO FALTANTES: CONCACAF.txt\n\n");
	}else if(UEFA == NULL){
		printf("ARCHIVO FALTANTES: UEFA.txt\n\n");
	}else if(CONME == NULL){
		printf("ARCHIVO FALTANTES: CONME.txt\n\n");
	}else if(AFC == NULL){
		printf("ARCHIVO FALTANTES: AFC.txt\n\n");
	}
	else{
		while(feof(AFC) == 0){			
			char caracter = fgetc(AFC);
			printf("%c", caracter);
		}
	}
}

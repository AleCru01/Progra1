#include <stdio.h>
#include <stdlib.h> //libreria para definir la funcion Exit(1) y terminar el programa
#include "Procesos.h" //Librer�a general para TODOS los procesos comunes 
#include <time.h>
#include <string.h>
void definirCupos();
void clasificacion(FILE *confederacion, int cupos, int playoffs);
void repechaje(); //para sacar 2 paises de repechaje 
//defini el archivo donde voy a guardar todos los datos, como GLOBAL 
FILE *PaisesCla;
FILE *PaisesRepechaje;
void CreacionGrupos();


//proceso de abrir los documentos:
void InicioClasificacion(){
	//proceso de leer los archivos .txt donde estan la lista de los paises y su ranking fifa
	FILE *CONCA = fopen("Recursos/Confederacion/CONCACAF.txt", "r"); //america del norte
	FILE *UEFA = fopen("Recursos/Confederacion/UEFA.txt", "r"); //Europa
	FILE *CONME = fopen("Recursos/Confederacion/CONMEBOL.txt", "r"); //Sudamerica
	FILE *AFC = fopen("Recursos/Confederacion/AFC.txt", "r"); //Asia 
	FILE *CAF = fopen("Recursos/Confederacion/CAF.txt", "r"); //Africa
	FILE *OFC = fopen("Recursos/Confederacion/OFC.txt", "r"); //Oceania
	
	//archivo paises clasi
	PaisesCla = fopen("Recursos/PaisesFinales.txt", "w");
	PaisesRepechaje = fopen("Recursos/Repechaje.txt", "w");
	
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
    
    fclose(PaisesRepechaje);
}


void clasificacion(FILE *confederacion, int cupos, int playoffs){
	if(cupos == 3){
		//esta condicion fue hecha para detectar si te estan pasando como parametro
		//a la CONCACAF y agregarle directamente a los anfitriones, queria comparar 
		//los punteros FILE *confederacion con FILE *CONCA pero tendria que pasarlo
		//como parametro y ne, mjr este 3 porque igual CONCA solo tiene 3 cupos directos
		
		fprintf(PaisesCla, "Estados-Unidos 1649\nMexico 1647\nCanada 1532\n");
	}
	
	char **nombres = NULL;
	int *rankings = NULL;
	int cantidad = 0;
	int LugaresDirectos[cupos]; 
	int PlayOff[playoffs];
	
	obtenerDatosConfederacion(confederacion, &nombres, &rankings, &cantidad);
	
printf(" .--.              .--.       .-.                         _             \n");
printf(": .--'            : .-'       : :                        :_;            \n");
printf(": :    .--. ,-.,-.: `;.--.  .-' : .--. .--.  .--.   .--. .-. .--. ,-.,-.\n");
printf(": :__ ' .; :: ,. :: :' '_.'' .; :' '_.': ..'' .; ; '  ..': :' .; :: ,. :\n");
printf("`.__.'`.__.':_;:_;:_;`.__.'`.__.'`.__.':_;  `.__,_;`.__.':_;`.__.':_;:_;\n\n");
                                                                        
                                                                        

	int i;
	for(i = 0; i<cantidad; i++){
		printf("%s - %d \n", nombres[i], rankings[i]);
	}
	printf("\n***************************************************");
	printf("\nEL numero de paises en esta confederacion es: %d\n", cantidad);
	//ruleta
	
	long sumatoria=0;
	for(i = 0; i<cantidad; i++){
		sumatoria += rankings[i];
	}
	printf("Con una puntuacion total de: %ld\n", sumatoria);
	printf("Esta tiene %d Cupos para el mundial\n", cupos);
	printf("Con %d Lugares para repechaje\n", playoffs);
	printf("***************************************************\n");
	//se que esto no se debe de hacer, pero voy a asignarle como todos los espacios en-1 a LugaresDirectos, pq asi puedo garantizar que 
	//al no estar definido el valor de cada punto, esta mal pero es la forma mas rapido que pense
	for(i = 0; i<cupos; i++){
		LugaresDirectos[i] = -1;
		if(i < playoffs){
			//hago el mismo proceso de poner en -1 como indefinido
			PlayOff[i] = -1; 
		}
	}
	printf("\n\nCLASIFICADOS: \n");
	printf("_______________________\n");
	for(i = 0; i<cupos; i++){
		LugaresDirectos[i] = sacarUnSelec(sumatoria, rankings, cantidad,LugaresDirectos, cupos,PlayOff, playoffs);
		
		//lo escribimos en el documento
		fprintf(PaisesCla,"%s %d\n", nombres[LugaresDirectos[i]], rankings[LugaresDirectos[i]]);
		//lo escribimos en pantalla
		printf("Pais Clasificado: %s con ranking %d\n", nombres[LugaresDirectos[i]], rankings[LugaresDirectos[i]]);
		sumatoria -= rankings[LugaresDirectos[i]];
		
	}
	
	printf("\nPLAYOFFS: \n");
	printf("______________\n");
	//FALTAN LOS REPECHAJES
	for(i = 0; i<playoffs; i++){
		//mando a llamar la funcion de sacar un selec
		PlayOff[i] = sacarUnSelec(sumatoria, rankings,cantidad, LugaresDirectos,playoffs,PlayOff, playoffs);
		
		//lo escribimos en el documento
		fprintf(PaisesRepechaje,"%s %d\n", nombres[PlayOff[i]], rankings[PlayOff[i]]);
		printf("Pais Clasificado para repechaje: %s con ranking %d\n", nombres[PlayOff[i]], rankings[PlayOff[i]]);
		sumatoria -= rankings[PlayOff[i]];
	}
	
	liberarDatosConfederacion(nombres, rankings, cantidad);
}



void repechaje(){
	
	printf("*********************\n");
	printf("* FASE DE REPECHAJE *\n");
	printf("*********************\n\n\n");
	
	
	//abrimos el archivo para leer
	PaisesRepechaje = fopen("Recursos/Repechaje.txt", "r");
	
	//guardamos los paises:
	char **nombres = NULL;
	int *rankings = NULL;
	int cantidad = 0;

	//obtenemos los datos
	obtenerDatosConfederacion(PaisesRepechaje, &nombres, &rankings, &cantidad);
	
	//sacamos numeros aleatorios, pero de plano ya no tienen peso, ya son solo numeros al asar
	int numeros[2] = {-1, -1};
	numeros[0] = ElegirUltimosLugares(rankings, numeros, 6);
	numeros[1] = ElegirUltimosLugares(rankings, numeros, 6);
	
	printf("Pais clasificado por repechaje 1: %s\n", nombres[numeros[0]]);
	printf("Pais clasificado por repechaje 2: %s\n", nombres[numeros[1]]);
	
	//escibimos en archivo
	fprintf(PaisesCla,"%s %d\n", nombres[numeros[0]], rankings[numeros[0]]);
	fprintf(PaisesCla,"%s %d", nombres[numeros[1]], rankings[numeros[1]]);
	//cerramos el archivo
	fclose(PaisesRepechaje);
	fclose(PaisesCla);
}



////////////////////////////
//CREACION DE GRUPOS


int sacarUnNumero(int usados[], int max) {
    int num;

    do {
        num = rand() % max;
    } while (usados[num]); // si ya fue usado, sigue buscando

    usados[num] = 1; // marcar como usado
    return num;
}

struct Grupo {
	//ponemos 4 pq son 4 equipos alv
    int idGrupo;
    char *nombres[4];
    int rankings[4];
    int puntos[4];
};

void imprimirGrupos(struct Grupo grupos[]) {
	FILE *archivo = fopen("Grupos.txt", "w");
	int i, j;
    for (i = 0; i < 12; i++) {
        printf("\nGrupo %c\n", 'A' + i);
        fprintf(archivo, "Grupo %c --------------------\n", 'A'+i);
        for (j = 0; j < 4; j++) {
        	fprintf(archivo,"  %s - %d puntos (ranking: %d)\n",grupos[i].nombres[j],grupos[i].puntos[j],grupos[i].rankings[j]);
            printf("  %s - %d puntos (ranking: %d)\n",grupos[i].nombres[j],grupos[i].puntos[j],grupos[i].rankings[j]);
        }
    }
    fclose(archivo);
}



void CreacionGrupos(){
	struct Grupo grupos[12];
    FILE *archivo = fopen("Recursos/PaisesFinales.txt", "r");
    if(!archivo){
    	printf("NO SE PUDO ABRIR ARCHIVO PARA CREAR LOS GRUPOS");
	}
    //Obtener datos: 
    char **nombres;
    int *rankings;
    int cantidad = 0;
    int i, j, a,b;
    obtenerDatosConfederacion(archivo, &nombres, &rankings, &cantidad);
    
    int usados[48] = {0};  // inicializar todos en 0

	for(i = 0; i < 12; i++) {
	    for(j = 0; j < 4; j++) {
	        int num = sacarUnNumero(usados,48);
	        grupos[i].nombres[j] = strdup(nombres[num]); 
	        grupos[i].rankings[j] = rankings[num]; 
	        grupos[i].puntos[j] = 0;
	    }
	}
    
    imprimirGrupos(grupos);
    
    printf("Presione una tecla para saber quien paso...");
    getch();
    system("cls");
    
printf(" ######                                                                     \n");
printf(" #     # ######  ####  #  ####  ###### #  ####    ##   #    #  ####   ####  \n");
printf(" #     # #      #      # #      #      # #       #  #  #    # #    # #      \n");
printf(" #     # #####   ####  #  ####  #####  #  ####  #    # #    # #    #  ####  \n");
printf(" #     # #           # #      # #      #      # ###### #    # #    #      # \n");
printf(" #     # #      #    # # #    # #      # #    # #    #  #  #  #    # #    # \n");
printf(" ######  ######  ####  #  ####  ###### #  ####  #    #   ##    ####   ####  \n\n\n");
                                                                            

    FILE *desiseisavos = fopen("Diesis.txt", "w");
    
    //vamos a sacar los 2 clasificados 
    for(i = 0; i<12; i++){
		int grupo[4] = {0};
    	for(j = 0; j<2; j++){
    		int num = sacarUnNumero(grupo,4);
    		fprintf(desiseisavos, "%s %d\n", grupos[i].nombres[num], grupos[i].rankings[num]);
    		printf("El pais que avanza es: %s con %d\n", grupos[i].nombres[num], grupos[i].rankings[num]);
		}
		if(i < 8){
			int num = sacarUnNumero(grupo,4);
    		fprintf(desiseisavos, "%s %d\n", grupos[i].nombres[num], grupos[i].rankings[num]);
    		printf("El pais que avanza es: %s con %d\n", grupos[i].nombres[num], grupos[i].rankings[num]);
		}
	}
	
    fclose(desiseisavos);
    
    printf("Presione cualquier tecla para continuar...");
    getch();
    system("cls");
    
                                                 
printf("\n\n  ####   ####  #####   ##   #    #  ####   ####  \n");
printf(" #    # #    #   #    #  #  #    # #    # #      \n");
printf(" #    # #        #   #    # #    # #    #  ####  \n");
printf(" #    # #        #   ###### #    # #    #      # \n");
printf(" #    # #    #   #   #    #  #  #  #    # #    # \n");
printf("  ####   ####    #   #    #   ##    ####   ####  \n\n\n");
                                                 

    
    
    desiseisavos = fopen("Diesis.txt", "r");
    
    free(nombres);
    free(rankings);
    
    //OCTAVOS
    FILE *octavos = fopen("octavos.txt", "w");
    
    //volvemos a leer
    
    obtenerDatosConfederacion(desiseisavos, &nombres, &rankings, &cantidad);
    int oct[16] = {0};
    for(i = 0; i<16; i++){
    	int num = sacarUnNumero(oct,32);
    	fprintf(octavos, "%s %d\n", nombres[num], rankings[num]);
    	printf("El pais que avanza es: %s con %d\n", nombres[num], rankings[num]);
	}
	
	//cuartos
	fclose(desiseisavos);
	fclose(octavos);
	
	octavos = fopen("octavos.txt", "r");
	printf("Presione cualquier tecla para continuar...");
    getch();
    system("cls");
    
    
                                                 
printf("  ####  #    #   ##   #####  #####  ####   ####  \n");
printf(" #    # #    #  #  #  #    #   #   #    # #      \n");
printf(" #      #    # #    # #    #   #   #    #  ####  \n");
printf(" #      #    # ###### #####    #   #    #      # \n");
printf(" #    # #    # #    # #   #    #   #    # #    # \n");
printf("  ####   ####  #    # #    #   #    ####   ####  \n\n");
                                                 

	free(nombres);
    free(rankings);
    
    //OCTAVOS
    FILE *cuartos = fopen("cuartos.txt", "w");
    
    //volvemos a leer
    
    obtenerDatosConfederacion(octavos, &nombres, &rankings, &cantidad);
	int cuar[8] = {0};
    for(i = 0; i<8; i++){
    	int num = sacarUnNumero(cuar,16);
    	fprintf(cuartos, "%s %d\n", nombres[num], rankings[num]);
    	printf("El pais que avanza es: %s con %d\n", nombres[num], rankings[num]);
	}
	
	////////SEMIS
	fclose(octavos);
	fclose(cuartos);
	
	cuartos = fopen("cuartos.txt", "r");
	printf("Presione cualquier tecla para continuar...");
    getch();
    system("cls");
    
                                                      
printf("  ####  ###### #    # # ###### # #    #   ##   #      \n");
printf(" #      #      ##  ## # #      # ##   #  #  #  #      \n");
printf("  ####  #####  # ## # # #####  # # #  # #    # #      \n");
printf("      # #      #    # # #      # #  # # ###### #      \n");
printf(" #    # #      #    # # #      # #   ## #    # #      \n");
printf("  ####  ###### #    # # #      # #    # #    # ###### \n\n");
                                                      

	
	free(nombres);
    free(rankings);
    
    //OCTAVOS
    FILE *semis = fopen("semis.txt", "w");
    
    //volvemos a leer
    
    obtenerDatosConfederacion(cuartos, &nombres, &rankings, &cantidad);
	int semi[4] = {0};
    for(i = 0; i<4; i++){
    	int num = sacarUnNumero(semi,8);
    	fprintf(semis, "%s %d\n", nombres[num], rankings[num]);
    	printf("El pais que avanza es: %s con %d\n", nombres[num], rankings[num]);
	}
	
	////////FINAL
	fclose(cuartos);
	fclose(semis);
	
	semis = fopen("semis.txt", "r");
	printf("Presione cualquier tecla para continuar...");
    getch();
    system("cls");
    
                                                      

                               
printf(" ###### # #    #   ##   #      \n");
printf(" #      # ##   #  #  #  #      \n");
printf(" #####  # # #  # #    # #      \n");
printf(" #      # #  # # ###### #      \n");
printf(" #      # #   ## #    # #      \n");
printf(" #      # #    # #    # ###### \n\n");
                               

                                                      

	
	free(nombres);
    free(rankings);
    
    //OCTAVOS
    FILE *final = fopen("final.txt", "w");
    
    //volvemos a leer
    
    obtenerDatosConfederacion(semis, &nombres, &rankings, &cantidad);
	int fin[2] = {0};
    for(i = 0; i<2; i++){
    	int num = sacarUnNumero(fin,4);
    	fprintf(final, "%s %d\n", nombres[num], rankings[num]);
    	printf("El pais que avanza es: %s con %d\n", nombres[num], rankings[num]);
	}
	
	////////GANADOR
	fclose(semis);
	fclose(final);
	
	final = fopen("final.txt", "r");
	printf("Presione cualquier tecla para continuar...");
    getch();
    system("cls");
    
                                                      

                                                  
printf("  ####    ##   #    #   ##   #####   ####  #####  \n");
printf(" #    #  #  #  ##   #  #  #  #    # #    # #    # \n");
printf(" #      #    # # #  # #    # #    # #    # #    # \n");
printf(" #  ### ###### #  # # ###### #    # #    # #####  \n");
printf(" #    # #    # #   ## #    # #    # #    # #   #  \n");
printf("  ####  #    # #    # #    # #####   ####  #    # \n\n");
                                                  


                                                      

	
	free(nombres);
    free(rankings);
    
    //OCTAVOS
    FILE *ganador = fopen("ganador.txt", "w");
    
    //volvemos a leer
    
    obtenerDatosConfederacion(final, &nombres, &rankings, &cantidad);
	int gan[1] = {0};
    for(i = 0; i<1; i++){
    	int num = sacarUnNumero(gan,2);
    	fprintf(ganador, "%s %d\n", nombres[num], rankings[num]);
    	printf("EL CAMPEON es: %s con %d\n", nombres[num], rankings[num]);
	}
	
	
	
	
	
    // Liberar memoria usada para nombres
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 4; j++) {
            free(grupos[i].nombres[j]);
        }
    }
	 
	for (i = 0; i < cantidad; i++) free(nombres[i]);
	
    free(nombres);
    free(rankings);
}

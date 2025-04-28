#include <stdio.h>
#include <stdlib.h>


///Cuando llamen la funcion pongan el archivo como variable "*archivo= CONCA"
void CONCACAF(FILE *archivo) {
    char a[1000]; 
    int i = 0;
    char c;

    while ((c = fgetc(archivo)) != EOF && i < sizeof(a) - 1) {
        a[i] = c;
        i++;
    }

    a[i] = '\0'; 

    printf("Contenido del archivo:\n%s\n", a);
}

void UEFA2(FILE *archivo2) {
    char a[1000]; 
    int i = 0;
    char c;

    while ((c = fgetc(archivo2)) != EOF && i < sizeof(a) - 1) {
        a[i] = c;
        i++;
    }

    a[i] = '\0'; 

    printf("Contenido del archivo:\n%s\n", a);
}
void CONM(FILE *archivo3) {
    char a[1000]; 
    int i = 0;
    char c;

    while ((c = fgetc(archivo3)) != EOF && i < sizeof(a) - 1) {
        a[i] = c;
        i++;
    }

    a[i] = '\0'; 

    printf("Contenido del archivo:\n%s\n", a);
}
void AFC2(FILE *archivo4) {
    char a[1000]; 
    int i = 0;
    char c;

    while ((c = fgetc(archivo4)) != EOF && i < sizeof(a) - 1) {
        a[i] = c;
        i++;
    }

    a[i] = '\0'; 

    printf("Contenido del archivo:\n%s\n", a);
}
void CAF1(FILE *archivo5) {
    char a[1000]; 
    int i = 0;
    char c;

    while ((c = fgetc(archivo5)) != EOF && i < sizeof(a) - 1) {
        a[i] = c;
        i++;
    }

    a[i] = '\0'; 

    printf("Contenido del archivo:\n%s\n", a);
}
void OFC1(FILE *archivo6) {
    char a[1000]; 
    int i = 0;
    char c;

    while ((c = fgetc(archivo6)) != EOF && i < sizeof(a) - 1) {
        a[i] = c;
        i++;
    }

    a[i] = '\0'; 

    printf("Contenido del archivo:\n%s\n", a);
}

int main() {
	//Es un ejemplo solo de el primer archivo
    FILE *CONCA = fopen("Confederacion/CONCACAF.txt", "r");

    if (!CONCA) { 
        printf("ARCHIVO FALTANTE: CONCACAF.txt\n\n");
        exit(1);
    }

    CONCACAF(CONCA);
    fclose(CONCA);
}
 

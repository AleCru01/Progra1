#include <stdio.h>

void dibujarPiramide(int altura) {
    for (int i = 1; i <= altura; i++) {
        // Imprimir espacios
        for (int j = 0; j < altura - i; j++) {
            printf(" ");
        }
        // Imprimir asteriscos
        for (int k = 0; k < (2 * i - 1); k++) {
            printf("*");
        }
        // Nueva línea después de cada fila
        printf("\n");
    }
}

int main() {
    int altura;
    printf("Introduce la altura de la pirámide: ");
    scanf("%d", &altura);
    dibujarPiramide(altura);
    return 0;
}


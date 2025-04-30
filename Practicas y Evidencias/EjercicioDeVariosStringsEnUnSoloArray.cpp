#include <stdio.h>
#include <string.h>

int main() {
    // Definimos un array de cadenas de texto
    char *cadenas[] = {
        "Hola",
        "Mundo",
        "Esto",
        "Es",
        "Un",
        "Array",
        "De",
        "Cadenas",
        "HOLA ALV"
    };

    // Calculamos el número de elementos en el array
    int numCadenas = sizeof(cadenas) / sizeof(cadenas[0]);

    // Imprimimos cada cadena de texto
    for (int i = 0; i < numCadenas; i++) {
        printf("%s\n", cadenas[i]);
    }

    return 0;
}

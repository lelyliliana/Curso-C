#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 3 };

int main(void)
{
    int datos[CAPACIDAD] = {4, 0, 0};
    size_t usados = 1;
    const int propuestas[] = {7, 0, 9};
    const size_t cantidad = sizeof propuestas / sizeof propuestas[0];
    for (size_t i = 0; i < cantidad; i++) {
        if (usados >= CAPACIDAD) {
            printf("Sin espacio para %d.\n", propuestas[i]);
            continue;
        }
        datos[usados] = propuestas[i];
        usados++;
    }
    printf("Usados: %zu\n", usados);
    for (size_t i = 0; i < usados; i++) {
        printf("Dato %zu: %d\n", i, datos[i]);
    }
    return EXIT_SUCCESS;
}

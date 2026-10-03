#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 5 };

int main(void)
{
    int datos[CAPACIDAD] = {0};
    size_t usados = 0;
    const int nuevo = 18;
    if (usados >= CAPACIDAD) {
        puts("Coleccion llena.");
        return EXIT_FAILURE;
    }
    datos[usados] = nuevo;
    usados++;
    if (usados >= CAPACIDAD) {
        puts("Coleccion llena.");
        return EXIT_FAILURE;
    }
    datos[usados] = 0;
    usados++;
    printf("Capacidad: %d; usados: %zu\n", CAPACIDAD, usados);
    for (size_t i = 0; i < usados; i++) {
        printf("Dato %zu: %d\n", i, datos[i]);
    }
    return EXIT_SUCCESS;
}

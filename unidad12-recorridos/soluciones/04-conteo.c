#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 6 };

int main(void)
{
    const int codigos[CAPACIDAD] = {2, 0, 2, 7, 2, 0};
    const size_t usados = 6;
    const int buscado = 2;
    size_t coincidencias = 0;
    if (usados > CAPACIDAD) {
        puts("Cantidad invalida.");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < usados; i++) {
        if (codigos[i] == buscado) {
            coincidencias++;
        }
    }
    printf("Coincidencias de %d: %zu\n", buscado, coincidencias);
    return EXIT_SUCCESS;
}

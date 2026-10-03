#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 5 };

int main(void)
{
    int datos[CAPACIDAD] = {4, 0, 7, 2, 9};
    const size_t usados = 5;
    if (usados > CAPACIDAD) {
        puts("Cantidad invalida.");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < usados / 2; i++) {
        const size_t opuesto = usados - 1 - i;
        const int temporal = datos[i];
        datos[i] = datos[opuesto];
        datos[opuesto] = temporal;
    }
    printf("Usados: %zu\n", usados);
    for (size_t i = 0; i < usados; i++) {
        printf("Valor: %d\n", datos[i]);
    }
    return EXIT_SUCCESS;
}

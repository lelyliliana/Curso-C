#include "filtro.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const int origen[] = {8, 2, 0, 10, 5};
    int destino[3] = {0};
    size_t usados = 0;
    if (!filtrar_minimo(origen, sizeof origen / sizeof origen[0], 5,
                        destino, sizeof destino / sizeof destino[0], &usados)) {
        puts("Filtro rechazado.");
        return EXIT_FAILURE;
    }
    printf("Seleccionadas: %zu\n", usados);
    for (size_t i = 0; i < usados; i++) {
        printf("Valor: %d\n", destino[i]);
    }
    return EXIT_SUCCESS;
}

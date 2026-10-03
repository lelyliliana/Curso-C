#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { CAPACIDAD = 6 };

int main(void)
{
    const char origen[] = "Leli";
    char destino[CAPACIDAD] = {0};
    const size_t longitud = strlen(origen);
    if (longitud >= sizeof destino) {
        puts("Texto demasiado largo.");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < longitud; i++) {
        destino[i] = origen[i];
    }
    destino[longitud] = '\0';
    printf("Copia: %s\nLongitud: %zu\n", destino, strlen(destino));
    return EXIT_SUCCESS;
}

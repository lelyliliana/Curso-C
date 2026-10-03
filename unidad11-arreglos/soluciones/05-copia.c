#include <stddef.h>
#include <stdio.h>

enum { CANTIDAD = 4 };

int main(void)
{
    const int original[CANTIDAD] = {4, 0, 7, 2};
    int copia[CANTIDAD] = {0};
    for (size_t i = 0; i < CANTIDAD; i++) {
        copia[i] = original[i];
    }
    copia[1] = 9;
    for (size_t i = 0; i < CANTIDAD; i++) {
        printf("Indice %zu: original %d, copia %d\n", i, original[i], copia[i]);
    }
    return 0;
}

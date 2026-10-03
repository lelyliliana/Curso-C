#include <stddef.h>
#include <stdio.h>

int main(void)
{
    int existencias[] = {12, 7, 0, 9};
    const size_t cantidad = sizeof existencias / sizeof existencias[0];
    for (size_t i = 0; i < cantidad; i++) {
        printf("Indice %zu: %d\n", i, existencias[i]);
    }
    printf("Elementos: %zu\n", cantidad);
    return 0;
}

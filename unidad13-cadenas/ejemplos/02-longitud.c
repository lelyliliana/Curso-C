#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char nombre[12] = "Leli";
    const size_t longitud = strlen(nombre);
    printf("Texto: %s\nCapacidad: %zu\nLongitud: %zu\n", nombre, sizeof nombre, longitud);
    for (size_t i = 0; i < longitud; i++) {
        printf("Indice %zu: %c\n", i, nombre[i]);
    }
    nombre[0] = 'M';
    printf("Modificado: %s\n", nombre);
    return 0;
}

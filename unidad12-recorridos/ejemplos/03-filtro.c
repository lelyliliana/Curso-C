#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 5 };

int main(void)
{
    const int lecturas[CAPACIDAD] = {8, 2, 0, 10, 5};
    const size_t usados = 5;
    const int umbral = 5;
    int seleccionadas[CAPACIDAD] = {0};
    size_t seleccionados = 0;
    if (usados > CAPACIDAD) {
        puts("Cantidad invalida.");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < usados; i++) {
        if (lecturas[i] < 0 || lecturas[i] > 100) {
            puts("Lectura fuera de rango.");
            return EXIT_FAILURE;
        }
        if (lecturas[i] >= umbral) {
            if (seleccionados >= CAPACIDAD) {
                puts("Sin espacio en destino.");
                return EXIT_FAILURE;
            }
            seleccionadas[seleccionados] = lecturas[i];
            seleccionados++;
        }
    }
    printf("Seleccionadas: %zu\n", seleccionados);
    for (size_t i = 0; i < seleccionados; i++) {
        printf("Valor: %d\n", seleccionadas[i]);
    }
    return EXIT_SUCCESS;
}

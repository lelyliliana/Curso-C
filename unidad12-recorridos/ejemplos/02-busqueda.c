#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 5 };

int main(void)
{
    const int codigos[CAPACIDAD] = {8, 2, 8, 0, 5};
    const size_t usados = 5;
    const int buscado = 8;
    if (usados > CAPACIDAD) {
        puts("Cantidad invalida.");
        return EXIT_FAILURE;
    }
    size_t posicion = usados;
    for (size_t i = 0; i < usados; i++) {
        if (codigos[i] == buscado) {
            posicion = i;
            break;
        }
    }
    if (posicion == usados) {
        puts("No encontrado.");
    } else {
        printf("Primera coincidencia: indice %zu, valor %d\n", posicion, codigos[posicion]);
    }
    return EXIT_SUCCESS;
}

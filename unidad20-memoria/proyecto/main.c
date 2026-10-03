#include "numeros.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    struct Numeros lista = {0};
    const int valores[] = {0, 25, 100, 40, 60};
    for (size_t i = 0; i < sizeof valores / sizeof valores[0]; ++i) {
        if (!agregar_numero(&lista, valores[i])) {
            liberar_numeros(&lista);
            fputs("No se pudo agregar.\n", stderr);
            return EXIT_FAILURE;
        }
    }
    printf("Usados: %zu; capacidad: %zu\n", lista.usados, lista.capacidad);
    for (size_t i = 0; i < lista.usados; ++i) printf("%d\n", lista.datos[i]);
    liberar_numeros(&lista);
    printf("Tras liberar: %zu %zu\n", lista.usados, lista.capacidad);
    return EXIT_SUCCESS;
}

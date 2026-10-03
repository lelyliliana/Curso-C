#include "../proyecto/numeros.h"
#include "../../unidad16-lineas/proyecto/entrada.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    char linea[33];
    int cantidad = 0;
    struct Numeros lista = {0};
    puts("Cantidad (0..10):");
    enum EstadoLinea estado = leer_linea(linea, sizeof linea);
    if (estado != LINEA_OK || !convertir_entero(linea, 0, 10, &cantidad)) {
        fputs("Cantidad invalida.\n", stderr);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < cantidad; ++i) {
        int valor = 0;
        printf("Valor %d (0..100):\n", i + 1);
        estado = leer_linea(linea, sizeof linea);
        if (estado != LINEA_OK || !convertir_entero(linea, 0, 100, &valor) ||
            !agregar_numero(&lista, valor)) {
            liberar_numeros(&lista);
            fputs("Coleccion incompleta.\n", stderr);
            return EXIT_FAILURE;
        }
    }
    unsigned long total = 0;
    for (size_t i = 0; i < lista.usados; ++i) total += (unsigned long)lista.datos[i];
    printf("Cantidad: %zu; total: %lu\n", lista.usados, total);
    liberar_numeros(&lista);
    return EXIT_SUCCESS;
}

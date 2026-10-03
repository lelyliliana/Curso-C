#include "entrada.h"
#include <stdio.h>
#include <stdlib.h>

static void informar_linea(enum EstadoLinea estado)
{
    switch (estado) {
    case LINEA_LARGA: puts("Linea demasiado larga."); break;
    case LINEA_INVALIDA: puts("Linea con byte no admitido."); break;
    case LINEA_ERROR: puts("Error de lectura."); break;
    default: puts("Argumentos de lectura invalidos."); break;
    }
}
int main(void)
{
    char linea[33] = {0};
    int valor = 0;
    puts("Entero de -1000 a 1000; linea de hasta 32 bytes.");
    const enum EstadoLinea estado = leer_linea(linea, sizeof linea);
    if (estado == LINEA_FIN) {
        puts("Fin sin numero.");
        return EXIT_SUCCESS;
    }
    if (estado != LINEA_OK) {
        informar_linea(estado);
        return EXIT_FAILURE;
    }
    if (!convertir_entero(linea, -1000, 1000, &valor)) {
        puts("Numero invalido.");
        return EXIT_FAILURE;
    }
    printf("Entero: %d\n", valor);
    return EXIT_SUCCESS;
}

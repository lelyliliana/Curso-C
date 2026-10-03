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
    double valor = 0;
    puts("Decimal de -50 a 150; punto decimal; hasta 32 bytes.");
    const enum EstadoLinea estado = leer_linea(linea, sizeof linea);
    if (estado == LINEA_FIN) {
        puts("Fin sin numero.");
        return EXIT_SUCCESS;
    }
    if (estado != LINEA_OK) {
        informar_linea(estado);
        return EXIT_FAILURE;
    }
    if (!convertir_decimal(linea, -50.0, 150.0, &valor)) {
        puts("Numero invalido.");
        return EXIT_FAILURE;
    }
    printf("Decimal: %.2f\n", valor);
    return EXIT_SUCCESS;
}

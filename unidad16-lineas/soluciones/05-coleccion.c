#include "entrada.h"
#include <stddef.h>
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
enum { CAPACIDAD = 3 };

int main(void)
{
    int datos[CAPACIDAD] = {0};
    size_t usados = 0;
    while (usados < CAPACIDAD) {
        char linea[33] = {0};
        printf("Dato %zu de 3: entero de 0 a 100.\n", usados + 1);
        const enum EstadoLinea estado = leer_linea(linea, sizeof linea);
        if (estado == LINEA_FIN) {
            puts("Coleccion incompleta.");
            return EXIT_FAILURE;
        }
        if (estado != LINEA_OK) {
            informar_linea(estado);
            return EXIT_FAILURE;
        }
        if (!convertir_entero(linea, 0, 100, &datos[usados])) {
            puts("Numero invalido.");
            return EXIT_FAILURE;
        }
        usados++;
    }
    int suma = 0;
    for (size_t i = 0; i < usados; i++) {
        suma += datos[i];
    }
    printf("Coleccion completa: %zu datos; suma %d.\n", usados, suma);
    return EXIT_SUCCESS;
}

#ifndef CURSO_C_RECIBO_H
#define CURSO_C_RECIBO_H

#include <stdbool.h>

/* Valida cantidad; las tres funciones de calculo requieren 0..100. */
bool cantidad_valida(int cantidad);
int subtotal_centavos(int cantidad);
int envio_centavos(int cantidad);
int total_centavos(int cantidad);

#endif

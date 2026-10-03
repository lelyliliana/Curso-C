#ifndef CURSO_C_FILTRO_H
#define CURSO_C_FILTRO_H
#include <stdbool.h>
#include <stddef.h>

/* cantidad <= 5; origen legible para cantidad int, cada uno en 0..100.
   destino escribible para capacidad int. usados escribible y separado.
   Origen, destino y salida de cantidad no se solapan.
   NULL en origen/destino solo con cantidad/capacidad cero, respectivamente.
   false no cambia destino ni *usados. */
bool filtrar_minimo(const int origen[], size_t cantidad, int umbral,
                    int destino[], size_t capacidad, size_t *usados);
#endif

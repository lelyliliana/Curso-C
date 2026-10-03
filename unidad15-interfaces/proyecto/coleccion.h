#ifndef CURSO_C_COLECCION_H
#define CURSO_C_COLECCION_H

#include <stdbool.h>
#include <stddef.h>

enum { MAX_LECTURAS = 5 };

/* Si 1 <= cantidad <= MAX_LECTURAS, datos permite leer cantidad int vivos.
   resultado apunta a un int modificable, separado del segmento de datos.
   Se comprueban cantidad <= MAX_LECTURAS y valores 0..100.
   false no modifica *resultado. */
bool sumar_lecturas(const int datos[], size_t cantidad, int *resultado);
/* Mismo contrato; minimo requiere al menos una lectura. */
bool minimo_lecturas(const int datos[], size_t cantidad, int *resultado);
/* origen es cadena terminada; destino permite escribir capacidad char.
   Regiones separadas, sin solapamiento. false no modifica destino. */
bool copiar_texto(const char origen[], char destino[], size_t capacidad);

#endif

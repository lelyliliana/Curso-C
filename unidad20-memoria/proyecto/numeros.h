#ifndef CURSO_C_NUMEROS_H
#define CURSO_C_NUMEROS_H
#include <stdbool.h>
#include <stddef.h>
enum { LIMITE_NUMEROS = 1000 };
struct Numeros { int *datos; size_t usados; size_t capacidad; };
/* Inicializar con {0}. Objeto vivo con propiedad exclusiva del bloque.
   No copiar por asignacion. Solo datos[0..usados) estan inicializados.
   Argumentos invalidos o falta de memoria: false, sin cambios.
   Capacidad solicitada 0 no asigna. Nunca reduce la reserva. */
bool reservar_numeros(struct Numeros *lista, size_t capacidad);
/* valor 0..100. Puede crecer e invalidar punteros prestados al bloque. */
bool agregar_numero(struct Numeros *lista, int valor);
/* NULL se admite. Lista inicializada: libera y restablece estado vacio. */
void liberar_numeros(struct Numeros *lista);
#endif

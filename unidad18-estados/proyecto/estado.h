#ifndef CURSO_C_ESTADO_H
#define CURSO_C_ESTADO_H
#include <stdbool.h>
enum Estado {APAGADO = 10, LISTO = 20, ACTIVO = 30, FALLO = 40};
enum Evento {ENCENDER = 1, INICIAR, DETENER, ERROR_DETECTADO, RESTABLECER};
/* estado es objeto vivo modificable. NULL, valores desconocidos o
   transiciones no admitidas devuelven false sin cambiarlo. */
bool transicionar(enum Estado *estado, enum Evento evento);
const char *nombre_estado(enum Estado estado);
#endif

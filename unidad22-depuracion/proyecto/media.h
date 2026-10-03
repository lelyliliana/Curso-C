#ifndef CURSO_C_MEDIA_H
#define CURSO_C_MEDIA_H
#include <stddef.h>
enum ResultadoMedia { MEDIA_OK, MEDIA_ARGUMENTO, MEDIA_VACIO, MEDIA_DATO };
/* cantidad 0..1000; datos apunta a cantidad enteros vivos legibles (0..100).
   NULL datos solo con cantidad cero. salida escribible y separada de datos.
   Rechazo conserva salida. Vacio no tiene media.
   El algoritmo defectuoso de ejemplos tiene esta misma interfaz para comparar. */
enum ResultadoMedia calcular_media(const int datos[], size_t cantidad, double *salida);
#endif

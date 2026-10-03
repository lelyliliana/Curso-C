#ifndef CURSO_C_ARCHIVO_H
#define CURSO_C_ARCHIVO_H
#include "../../unidad17-estructuras/proyecto/sensor.h"
enum ResultadoArchivo {ARCHIVO_OK, ARCHIVO_ARGUMENTO, ARCHIVO_ABRIR, ARCHIVO_FORMATO, ARCHIVO_CAPACIDAD, ARCHIVO_IO};
/* ruta es cadena terminada; hasta 3 registros vivos legibles.
   Crea exclusivamente un archivo nuevo (wx). No reemplaza uno existente.
   Un error de escritura/cierre puede dejar un archivo incompleto. */
enum ResultadoArchivo guardar_registros(const char *ruta, const struct Sensor datos[], size_t cantidad);
/* destino permite escribir capacidad registros; usados es salida separada.
   NULL destino solo con capacidad cero. Un rechazo conserva ambos.
   Admite maximo 3 registros y exige fin tras los declarados. */
enum ResultadoArchivo cargar_registros(const char *ruta, struct Sensor destino[], size_t capacidad, size_t *usados);
#endif

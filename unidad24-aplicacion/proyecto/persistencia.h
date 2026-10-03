#ifndef CURSO_C_PERSISTENCIA_H
#define CURSO_C_PERSISTENCIA_H
#include "../../unidad23-diseno/proyecto/agenda.h"
enum ResultadoPersistencia { PERSISTE_OK, PERSISTE_ARGUMENTO, PERSISTE_ABRIR, PERSISTE_FORMATO, PERSISTE_MEMORIA, PERSISTE_IO };
/* Formato C-AGENDA-1: 0..100 sensores con nombres unicos.
   rutas cadenas terminadas; catalogos propietarios validos vivos.
   Guardar crea wx, no reemplaza; un fallo IO puede dejar un archivo parcial. */
enum ResultadoPersistencia guardar_agenda(const char *ruta, const struct Catalogo *agenda);
/* Carga y cierre correctos antes de reemplazar. Fallo conserva destino. */
enum ResultadoPersistencia cargar_agenda(const char *ruta, struct Catalogo *destino);
#endif

#ifndef CURSO_C_CATALOGO_H
#define CURSO_C_CATALOGO_H
#include "../../unidad17-estructuras/proyecto/sensor.h"
enum { LIMITE_CATALOGO = 100 };
enum ResultadoCatalogo { CAT_OK, CAT_ARGUMENTO, CAT_LIMITE, CAT_MEMORIA, CAT_ARCHIVO };
struct Catalogo { struct Sensor *datos; size_t usados; size_t capacidad; };
/* Todos los catalogos se inicializan con {0}; propiedad exclusiva del bloque.
   Cantidades y capacidad son metadatos del modulo, no deben editarse.
   Los punteros recibidos son objetos vivos con permisos apropiados.
   Un rechazo no cambia el catalogo. sensor puede ser miembro de este mismo
   catalogo: se copia antes de cualquier crecimiento. */
enum ResultadoCatalogo agregar_sensor(struct Catalogo *catalogo, const struct Sensor *sensor);
/* Copia independiente. Ambos objetos inicializados y sin bloques compartidos.
   Autocopia es exito sin cambios. Reemplaza destino solo tras copia completa. */
enum ResultadoCatalogo clonar_catalogo(const struct Catalogo *origen, struct Catalogo *destino);
/* Objetos distintos e inicializados, sin bloques compartidos.
   Libera lo anterior de destino; transfiere propiedad y deja origen vacio. */
bool mover_catalogo(struct Catalogo *origen, struct Catalogo *destino);
/* Usa formato y maximo de 3 registros de Unidad 19, no LIMITE_CATALOGO.
   ruta es cadena terminada; salida completa o destino intacto. */
enum ResultadoCatalogo cargar_catalogo(const char *ruta, struct Catalogo *destino);
/* Lista inicializada; NULL admitido. Puede repetirse tras liberar. */
void liberar_catalogo(struct Catalogo *catalogo);
#endif

#ifndef CURSO_C_AGENDA_H
#define CURSO_C_AGENDA_H
#include "../../unidad21-recursos/proyecto/catalogo.h"
enum ResultadoAgenda { AGENDA_OK, AGENDA_ARGUMENTO, AGENDA_DUPLICADO, AGENDA_AUSENTE, AGENDA_LIMITE, AGENDA_MEMORIA };
struct ResumenAgenda {size_t cantidad; unsigned long total; int minimo; int maximo; double media;};
/* Catalogo inicializado con {0}, propietario exclusivo; registros validos con
   nombres unicos. No editar metadatos. Punteros vivos y permisos adecuados.
   nombres son cadenas terminadas separadas de salidas. Rechazo sin cambios. */
bool buscar_sensor(const struct Catalogo *agenda, const char *nombre, size_t *posicion);
enum ResultadoAgenda insertar_sensor(struct Catalogo *agenda, const char *nombre, int valor);
enum ResultadoAgenda actualizar_sensor(struct Catalogo *agenda, const char *nombre, int valor);
enum ResultadoAgenda quitar_sensor(struct Catalogo *agenda, const char *nombre);
/* Vacio devuelve false y conserva salida. salida no invade agenda ni datos. */
bool resumir_agenda(const struct Catalogo *agenda, struct ResumenAgenda *salida);
/* Comprueba forma, registros y unicidad. No certifica memoria ni propiedad. */
bool agenda_valida(const struct Catalogo *agenda);
#endif

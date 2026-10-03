#include "agenda.h"
#include <string.h>
bool agenda_valida(const struct Catalogo *a) {
    if (a == NULL || a->usados > a->capacidad || a->capacidad > LIMITE_CATALOGO ||
        (a->capacidad == 0 && a->datos != NULL) || (a->capacidad > 0 && a->datos == NULL)) return false;
    for (size_t i = 0; i < a->usados; ++i) {
        if (!sensor_valido(&a->datos[i])) return false;
        for (size_t j = 0; j < i; ++j)
            if (strcmp(a->datos[i].nombre, a->datos[j].nombre) == 0) return false;
    }
    return true;
}
bool buscar_sensor(const struct Catalogo *a, const char *nombre, size_t *posicion) {
    if (nombre == NULL || posicion == NULL || !agenda_valida(a)) return false;
    for (size_t i = 0; i < a->usados; ++i)
        if (strcmp(a->datos[i].nombre, nombre) == 0) { *posicion = i; return true; }
    return false;
}
enum ResultadoAgenda insertar_sensor(struct Catalogo *a, const char *nombre, int valor) {
    if (!agenda_valida(a)) return AGENDA_ARGUMENTO;
    struct Sensor nuevo;
    if (!crear_sensor(nombre, valor, &nuevo)) return AGENDA_ARGUMENTO;
    size_t posicion = 0;
    if (buscar_sensor(a, nuevo.nombre, &posicion)) return AGENDA_DUPLICADO;
    enum ResultadoCatalogo r = agregar_sensor(a, &nuevo);
    if (r == CAT_OK) return AGENDA_OK;
    if (r == CAT_LIMITE) return AGENDA_LIMITE;
    if (r == CAT_MEMORIA) return AGENDA_MEMORIA;
    return AGENDA_ARGUMENTO;
}
enum ResultadoAgenda actualizar_sensor(struct Catalogo *a, const char *nombre, int valor) {
    if (!agenda_valida(a) || nombre == NULL || valor < 0 || valor > 100) return AGENDA_ARGUMENTO;
    size_t posicion = 0;
    if (!buscar_sensor(a, nombre, &posicion)) return AGENDA_AUSENTE;
    a->datos[posicion].valor = valor;
    return AGENDA_OK;
}
enum ResultadoAgenda quitar_sensor(struct Catalogo *a, const char *nombre) {
    if (!agenda_valida(a) || nombre == NULL) return AGENDA_ARGUMENTO;
    size_t posicion = 0;
    if (!buscar_sensor(a, nombre, &posicion)) return AGENDA_AUSENTE;
    for (size_t i = posicion; i + 1 < a->usados; ++i) a->datos[i] = a->datos[i + 1];
    --a->usados;
    return AGENDA_OK;
}
bool resumir_agenda(const struct Catalogo *a, struct ResumenAgenda *salida) {
    if (salida == NULL || !agenda_valida(a) || a->usados == 0) return false;
    struct ResumenAgenda r = {.cantidad = a->usados, .total = 0,
        .minimo = a->datos[0].valor, .maximo = a->datos[0].valor, .media = 0};
    for (size_t i = 0; i < a->usados; ++i) {
        int valor = a->datos[i].valor;
        r.total += (unsigned long)valor;
        if (valor < r.minimo) r.minimo = valor;
        if (valor > r.maximo) r.maximo = valor;
    }
    r.media = (double)r.total / (double)r.cantidad;
    *salida = r;
    return true;
}

#include "catalogo.h"
#include "../../unidad19-archivos/proyecto/archivo.h"
#include <stdint.h>
#include <stdlib.h>
static bool forma_valida(const struct Catalogo *c) {
    return c != NULL && c->usados <= c->capacidad && c->capacidad <= LIMITE_CATALOGO &&
           ((c->capacidad == 0 && c->datos == NULL) || (c->capacidad > 0 && c->datos != NULL));
}
enum ResultadoCatalogo agregar_sensor(struct Catalogo *c, const struct Sensor *sensor) {
    if (!forma_valida(c) || !sensor_valido(sensor)) return CAT_ARGUMENTO;
    if (c->usados == LIMITE_CATALOGO) return CAT_LIMITE;
    struct Sensor copia = *sensor;
    if (c->usados == c->capacidad) {
        size_t nueva = c->capacidad == 0 ? 2 : c->capacidad * 2;
        if (nueva > LIMITE_CATALOGO) nueva = LIMITE_CATALOGO;
        if (nueva > SIZE_MAX / sizeof *c->datos) return CAT_LIMITE;
        struct Sensor *p = realloc(c->datos, nueva * sizeof *c->datos);
        if (p == NULL) return CAT_MEMORIA;
        c->datos = p;
        c->capacidad = nueva;
    }
    c->datos[c->usados] = copia;
    ++c->usados;
    return CAT_OK;
}
enum ResultadoCatalogo clonar_catalogo(const struct Catalogo *origen, struct Catalogo *destino) {
    if (!forma_valida(origen) || !forma_valida(destino)) return CAT_ARGUMENTO;
    if (origen == destino) return CAT_OK;
    for (size_t i = 0; i < origen->usados; ++i)
        if (!sensor_valido(&origen->datos[i])) return CAT_ARGUMENTO;
    struct Catalogo copia = {0};
    if (origen->usados != 0) {
        if (origen->usados > SIZE_MAX / sizeof *copia.datos) return CAT_LIMITE;
        copia.datos = malloc(origen->usados * sizeof *copia.datos);
        if (copia.datos == NULL) return CAT_MEMORIA;
        copia.capacidad = origen->usados;
        for (size_t i = 0; i < origen->usados; ++i) copia.datos[i] = origen->datos[i];
        copia.usados = origen->usados;
    }
    liberar_catalogo(destino);
    *destino = copia;
    return CAT_OK;
}
bool mover_catalogo(struct Catalogo *origen, struct Catalogo *destino) {
    if (!forma_valida(origen) || !forma_valida(destino) || origen == destino) return false;
    liberar_catalogo(destino);
    *destino = *origen;
    origen->datos = NULL;
    origen->usados = 0;
    origen->capacidad = 0;
    return true;
}
enum ResultadoCatalogo cargar_catalogo(const char *ruta, struct Catalogo *destino) {
    if (ruta == NULL || !forma_valida(destino)) return CAT_ARGUMENTO;
    struct Sensor registros[3];
    size_t usados = 0;
    enum ResultadoArchivo lectura = cargar_registros(ruta, registros, 3, &usados);
    if (lectura != ARCHIVO_OK) return CAT_ARCHIVO;
    struct Catalogo temporal = {0};
    for (size_t i = 0; i < usados; ++i) {
        enum ResultadoCatalogo resultado = agregar_sensor(&temporal, &registros[i]);
        if (resultado != CAT_OK) {
            liberar_catalogo(&temporal);
            return resultado;
        }
    }
    bool movido = mover_catalogo(&temporal, destino);
    if (!movido) { liberar_catalogo(&temporal); return CAT_ARGUMENTO; }
    return CAT_OK;
}
void liberar_catalogo(struct Catalogo *c) {
    if (c == NULL) return;
    free(c->datos);
    c->datos = NULL;
    c->usados = 0;
    c->capacidad = 0;
}

#include "agenda.h"
#include <assert.h>
#include <stdio.h>
#ifdef NDEBUG
#error Estas pruebas requieren assert activo
#endif
int main(void) {
    struct Catalogo a = {0};
    size_t posicion = 99;
    bool ok = buscar_sensor(&a, "A", &posicion);
    assert(!ok && posicion == 99);
    struct ResumenAgenda resumen = {.cantidad = 77};
    ok = resumir_agenda(&a, &resumen);
    assert(!ok && resumen.cantidad == 77);
    enum ResultadoAgenda r = insertar_sensor(&a, "A", 0); assert(r == AGENDA_OK);
    r = insertar_sensor(&a, "B", 100); assert(r == AGENDA_OK);
    r = insertar_sensor(&a, "A", 25); assert(r == AGENDA_DUPLICADO && a.usados == 2 && a.datos[0].valor == 0);
    r = actualizar_sensor(&a, "A", 101); assert(r == AGENDA_ARGUMENTO && a.datos[0].valor == 0);
    r = actualizar_sensor(&a, "ausente", 25); assert(r == AGENDA_AUSENTE);
    ok = resumir_agenda(&a, &resumen);
    assert(ok && resumen.cantidad == 2 && resumen.total == 100 && resumen.minimo == 0 && resumen.maximo == 100 && resumen.media == 50);
    r = quitar_sensor(&a, "A"); assert(r == AGENDA_OK && a.usados == 1 && a.datos[0].valor == 100);
    r = quitar_sensor(&a, "B"); assert(r == AGENDA_OK && a.usados == 0);
    r = quitar_sensor(&a, "B"); assert(r == AGENDA_AUSENTE);
    liberar_catalogo(&a);
    puts("Pruebas de agenda: OK.");
    return 0;
}

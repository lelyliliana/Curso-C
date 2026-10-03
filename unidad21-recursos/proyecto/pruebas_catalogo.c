#include "catalogo.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef NDEBUG
#error Estas pruebas requieren assert activo
#endif
int main(void) {
    struct Catalogo a = {0}, b = {0};
    struct Sensor sensor = {.nombre = "A", .valor = 25};
    enum ResultadoCatalogo r = agregar_sensor(&a, &sensor);
    assert(r == CAT_OK);
    r = agregar_sensor(&a, &a.datos[0]);
    assert(r == CAT_OK);
    /* El tercer agregado fuerza crecimiento con argumento interno. */
    r = agregar_sensor(&a, &a.datos[0]);
    assert(r == CAT_OK && a.usados == 3 && strcmp(a.datos[2].nombre, "A") == 0);
    r = clonar_catalogo(&a, &b);
    assert(r == CAT_OK && b.datos != a.datos && b.usados == 3);
    b.datos[0].valor = 99;
    assert(a.datos[0].valor == 25);
    r = clonar_catalogo(&a, &a);
    assert(r == CAT_OK);
    bool ok = mover_catalogo(&a, &a);
    assert(!ok && a.usados == 3);
    ok = mover_catalogo(&a, &b);
    assert(ok && a.datos == NULL && b.usados == 3 && b.datos[0].valor == 25);
    r = clonar_catalogo(&a, &b);
    assert(r == CAT_OK && b.datos == NULL);
    liberar_catalogo(&a);
    liberar_catalogo(&b);
    liberar_catalogo(&b);
    liberar_catalogo(NULL);
    puts("Pruebas de catalogo: OK.");
    return 0;
}

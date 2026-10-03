#include "../../unidad17-estructuras/proyecto/sensor.h"
#include <stdio.h>
static void mostrar(const struct Sensor *prestado) {
    printf("%s: %d\n", prestado->nombre, prestado->valor);
}
int main(void) {
    struct Sensor local = {.nombre = "patio", .valor = 25};
    mostrar(&local);
    /* mostrar observa; no libera un objeto automatico ajeno. */
    printf("Sigue vivo: %s\n", local.nombre);
    return 0;
}

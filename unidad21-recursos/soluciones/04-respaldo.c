#include "../proyecto/catalogo.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    struct Catalogo trabajo = {0}, respaldo = {0};
    struct Sensor s = {.nombre = "patio", .valor = 0};
    int salida = EXIT_FAILURE;
    if (agregar_sensor(&trabajo, &s) != CAT_OK) goto limpieza;
    if (clonar_catalogo(&trabajo, &respaldo) != CAT_OK) goto limpieza;
    trabajo.datos[0].valor = 100;
    printf("Trabajo: %d; respaldo: %d\n", trabajo.datos[0].valor, respaldo.datos[0].valor);
    if (!mover_catalogo(&respaldo, &trabajo)) goto limpieza;
    printf("Restaurado: %d; respaldo vacio: %zu\n", trabajo.datos[0].valor, respaldo.usados);
    salida = EXIT_SUCCESS;
limpieza:
    liberar_catalogo(&respaldo);
    liberar_catalogo(&trabajo);
    if (salida != EXIT_SUCCESS) fputs("No se pudo respaldar.\n", stderr);
    return salida;
}

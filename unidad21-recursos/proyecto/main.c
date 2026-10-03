#include "catalogo.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    struct Catalogo original = {0}, copia = {0}, final = {0};
    struct Sensor sensor = {.nombre = "patio", .valor = 25};
    int resultado = EXIT_FAILURE;
    if (agregar_sensor(&original, &sensor) != CAT_OK) goto limpieza;
    if (clonar_catalogo(&original, &copia) != CAT_OK) goto limpieza;
    copia.datos[0].valor = 40;
    printf("Original: %d; copia: %d\n", original.datos[0].valor, copia.datos[0].valor);
    if (!mover_catalogo(&copia, &final)) goto limpieza;
    printf("Origen movido: %zu; destino: %zu %d\n", copia.usados, final.usados, final.datos[0].valor);
    resultado = EXIT_SUCCESS;
limpieza:
    liberar_catalogo(&final);
    liberar_catalogo(&copia);
    liberar_catalogo(&original);
    if (resultado != EXIT_SUCCESS) fputs("Operacion rechazada.\n", stderr);
    return resultado;
}

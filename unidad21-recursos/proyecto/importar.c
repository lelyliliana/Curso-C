#include "catalogo.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    struct Catalogo catalogo = {0};
    struct Sensor anterior = {.nombre = "anterior", .valor = 77};
    if (argc != 2) { fputs("Uso: importar ruta\n", stderr); return EXIT_FAILURE; }
    if (agregar_sensor(&catalogo, &anterior) != CAT_OK) {
        liberar_catalogo(&catalogo);
        fputs("Sin memoria inicial.\n", stderr);
        return EXIT_FAILURE;
    }
    enum ResultadoCatalogo resultado = cargar_catalogo(argv[1], &catalogo);
    if (resultado != CAT_OK) {
        printf("Carga rechazada (%d); conserva %s %d\n", (int)resultado,
               catalogo.datos[0].nombre, catalogo.datos[0].valor);
        liberar_catalogo(&catalogo);
        return EXIT_FAILURE;
    }
    printf("Cargados: %zu\n", catalogo.usados);
    for (size_t i = 0; i < catalogo.usados; ++i)
        printf("%s: %d\n", catalogo.datos[i].nombre, catalogo.datos[i].valor);
    liberar_catalogo(&catalogo);
    return EXIT_SUCCESS;
}

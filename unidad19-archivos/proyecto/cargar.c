#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {puts("Uso: cargar ruta"); return EXIT_FAILURE;}
    struct Sensor datos[3] = {0};
    size_t usados = 0;
    enum ResultadoArchivo resultado = cargar_registros(argv[1], datos, 3, &usados);
    if (resultado != ARCHIVO_OK) {
        printf("No cargado; estado %d.\n", (int)resultado);
        return EXIT_FAILURE;
    }
    printf("Registros: %zu\n", usados);
    for (size_t i = 0; i < usados; i++) {printf("%s: %d\n", datos[i].nombre, datos[i].valor);}
    return EXIT_SUCCESS;
}

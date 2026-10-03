#include "archivo.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {puts("Uso: guardar ruta_nueva"); return EXIT_FAILURE;}
    const struct Sensor datos[] = {{"patio", 25}, {"salon", 0}, {"taller", 100}};
    enum ResultadoArchivo resultado = guardar_registros(argv[1], datos, 3);
    if (resultado != ARCHIVO_OK) {
        printf("No guardado; estado %d.\n", (int)resultado);
        return EXIT_FAILURE;
    }
    puts("Tres registros guardados en archivo nuevo.");
    return EXIT_SUCCESS;
}

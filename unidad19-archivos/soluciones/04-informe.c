#include "../proyecto/archivo.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {puts("Uso: informe ruta"); return EXIT_FAILURE;}
    struct Sensor datos[3] = {0};
    size_t usados = 0;
    enum ResultadoArchivo resultado = cargar_registros(argv[1], datos, 3, &usados);
    if (resultado != ARCHIVO_OK) {puts("Informe rechazado."); return EXIT_FAILURE;}
    int suma = 0;
    for (size_t i = 0; i < usados; i++) {suma += datos[i].valor;}
    printf("Registros: %zu\nSuma: %d\n", usados, suma);
    return EXIT_SUCCESS;
}

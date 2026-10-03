#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {puts("Uso: contar ruta"); return EXIT_FAILURE;}
    FILE *flujo = fopen(argv[1], "r");
    if (flujo == NULL) {puts("No se pudo abrir."); return EXIT_FAILURE;}
    size_t saltos = 0;
    bool exceso = false;
    int byte;
    while ((byte = fgetc(flujo)) != EOF) {
        if (byte == '\n') {
            if (saltos == 1000) {exceso = true; break;}
            saltos++;
        }
    }
    const int error = ferror(flujo);
    int cierre = fclose(flujo);
    if (error || cierre == EOF) {puts("Error de lectura o cierre."); return EXIT_FAILURE;}
    if (exceso) {puts("Mas de 1000 saltos: conteo rechazado."); return EXIT_FAILURE;}
    printf("Saltos de linea: %zu\n", saltos);
    return EXIT_SUCCESS;
}

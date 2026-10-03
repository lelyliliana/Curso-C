#include "../proyecto/persistencia.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {fputs("Uso: validar ruta\n", stderr); return EXIT_FAILURE;}
    struct Catalogo agenda = {0};
    enum ResultadoPersistencia r = cargar_agenda(argv[1], &agenda);
    if (r == PERSISTE_OK) printf("Archivo valido: %zu registros.\n", agenda.usados);
    else fprintf(stderr, "Archivo rechazado (%d).\n", (int)r);
    liberar_catalogo(&agenda);
    return r == PERSISTE_OK ? EXIT_SUCCESS : EXIT_FAILURE;
}

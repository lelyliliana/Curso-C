#include "../proyecto/agenda.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    struct Catalogo agenda = {0};
    int salida = EXIT_FAILURE;
    if (insertar_sensor(&agenda, "A", 0) != AGENDA_OK ||
        insertar_sensor(&agenda, "B", 50) != AGENDA_OK ||
        insertar_sensor(&agenda, "C", 100) != AGENDA_OK) goto limpieza;
    size_t encontrados = 0;
    for (size_t i = 0; i < agenda.usados; ++i) {
        if (agenda.datos[i].valor >= 50) {
            printf("%s: %d\n", agenda.datos[i].nombre, agenda.datos[i].valor);
            ++encontrados;
        }
    }
    printf("Encontrados: %zu; agenda: %zu\n", encontrados, agenda.usados);
    salida = EXIT_SUCCESS;
limpieza:
    liberar_catalogo(&agenda);
    if (salida != EXIT_SUCCESS) fputs("Sin informe.\n", stderr);
    return salida;
}

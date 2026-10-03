#include "agenda.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    struct Catalogo agenda = {0};
    int salida = EXIT_FAILURE;
    if (insertar_sensor(&agenda, "patio", 25) != AGENDA_OK) goto limpieza;
    if (insertar_sensor(&agenda, "salon", 0) != AGENDA_OK) goto limpieza;
    enum ResultadoAgenda r = insertar_sensor(&agenda, "patio", 99);
    printf("Duplicado rechazado: %s\n", r == AGENDA_DUPLICADO ? "si" : "no");
    if (actualizar_sensor(&agenda, "salon", 100) != AGENDA_OK) goto limpieza;
    struct ResumenAgenda resumen;
    if (!resumir_agenda(&agenda, &resumen)) goto limpieza;
    printf("Cantidad: %zu; total: %lu; media: %.2f\n", resumen.cantidad, resumen.total, resumen.media);
    if (quitar_sensor(&agenda, "patio") != AGENDA_OK) goto limpieza;
    printf("Queda: %s %d\n", agenda.datos[0].nombre, agenda.datos[0].valor);
    salida = EXIT_SUCCESS;
limpieza:
    liberar_catalogo(&agenda);
    if (salida != EXIT_SUCCESS) fputs("Proyecto rechazado.\n", stderr);
    return salida;
}

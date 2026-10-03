#include "../proyecto/media.h"
#include "../../unidad20-memoria/proyecto/numeros.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    struct Numeros lista = {0};
    const int valores[] = {0, 25, 100};
    int salida = EXIT_FAILURE;
    for (size_t i = 0; i < sizeof valores / sizeof valores[0]; ++i)
        if (!agregar_numero(&lista, valores[i])) goto limpieza;
    double media = -1.0;
    enum ResultadoMedia r = calcular_media(lista.datos, lista.usados, &media);
    if (r != MEDIA_OK) goto limpieza;
    printf("Cantidad: %zu; media: %.2f\n", lista.usados, media);
    salida = EXIT_SUCCESS;
limpieza:
    liberar_numeros(&lista);
    if (salida != EXIT_SUCCESS) fputs("Informe rechazado.\n", stderr);
    return salida;
}

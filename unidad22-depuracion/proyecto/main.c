#include "media.h"
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    const int datos[] = {1, 2};
    double media = -1.0;
    enum ResultadoMedia r = calcular_media(datos, 2, &media);
    if (r != MEDIA_OK) { fputs("Sin media valida.\n", stderr); return EXIT_FAILURE; }
    printf("Media: %.2f\n", media);
    return EXIT_SUCCESS;
}

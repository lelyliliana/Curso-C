#include "media.h"
#include <assert.h>
#include <stdio.h>
#ifdef NDEBUG
#error Estas pruebas requieren assert activo
#endif
static void comprobar(const int datos[], size_t cantidad, double esperado) {
    double salida = -1.0;
    enum ResultadoMedia r = calcular_media(datos, cantidad, &salida);
    assert(r == MEDIA_OK && salida > esperado - 0.000000001 && salida < esperado + 0.000000001);
}
int main(void) {
    const int fraccion[] = {1, 2}, iguales[] = {25, 25, 25}, extremos[] = {0, 100};
    comprobar(fraccion, 2, 1.5);
    comprobar(iguales, 3, 25.0);
    comprobar(extremos, 2, 50.0);
    double salida = 77.0;
    enum ResultadoMedia r = calcular_media(NULL, 0, &salida);
    assert(r == MEDIA_VACIO && salida == 77.0);
    const int invalido[] = {25, 101};
    r = calcular_media(invalido, 2, &salida);
    assert(r == MEDIA_DATO && salida == 77.0);
    r = calcular_media(NULL, 1, &salida);
    assert(r == MEDIA_ARGUMENTO && salida == 77.0);
    r = calcular_media(fraccion, 2, NULL);
    assert(r == MEDIA_ARGUMENTO);
    puts("Pruebas de media: OK.");
    return 0;
}

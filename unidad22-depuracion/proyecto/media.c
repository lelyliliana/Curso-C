#include "media.h"
enum ResultadoMedia calcular_media(const int datos[], size_t cantidad, double *salida) {
    if (salida == NULL || cantidad > 1000 || (datos == NULL && cantidad != 0)) return MEDIA_ARGUMENTO;
    if (cantidad == 0) return MEDIA_VACIO;
    unsigned long total = 0;
    for (size_t i = 0; i < cantidad; ++i) {
        if (datos[i] < 0 || datos[i] > 100) return MEDIA_DATO;
        total += (unsigned long)datos[i];
    }
    double media = (double)total / (double)cantidad;
    *salida = media;
    return MEDIA_OK;
}

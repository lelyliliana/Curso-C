#include "filtro.h"

bool filtrar_minimo(const int origen[], size_t cantidad, int umbral,
                    int destino[], size_t capacidad, size_t *usados)
{
    if (usados == NULL || cantidad > 5
        || (cantidad > 0 && origen == NULL)
        || (capacidad > 0 && destino == NULL)) {
        return false;
    }
    size_t necesarios = 0;
    for (size_t i = 0; i < cantidad; i++) {
        if (origen[i] < 0 || origen[i] > 100) {
            return false;
        }
        if (origen[i] >= umbral) {
            necesarios++;
        }
    }
    if (necesarios > capacidad) {
        return false;
    }
    size_t escritos = 0;
    for (size_t i = 0; i < cantidad; i++) {
        if (origen[i] >= umbral) {
            destino[escritos] = origen[i];
            escritos++;
        }
    }
    *usados = escritos;
    return true;
}

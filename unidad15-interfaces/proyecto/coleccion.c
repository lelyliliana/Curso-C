#include "coleccion.h"
#include <string.h>

static bool lecturas_validas(const int datos[], size_t cantidad)
{
    if (cantidad > MAX_LECTURAS || (cantidad > 0 && datos == NULL)) {
        return false;
    }
    for (size_t i = 0; i < cantidad; i++) {
        if (datos[i] < 0 || datos[i] > 100) {
            return false;
        }
    }
    return true;
}

bool sumar_lecturas(const int datos[], size_t cantidad, int *resultado)
{
    if (resultado == NULL || !lecturas_validas(datos, cantidad)) {
        return false;
    }
    int suma = 0;
    for (size_t i = 0; i < cantidad; i++) {
        suma += datos[i];
    }
    *resultado = suma;
    return true;
}

bool minimo_lecturas(const int datos[], size_t cantidad, int *resultado)
{
    if (resultado == NULL || cantidad == 0 || !lecturas_validas(datos, cantidad)) {
        return false;
    }
    int minimo = datos[0];
    for (size_t i = 1; i < cantidad; i++) {
        if (datos[i] < minimo) {
            minimo = datos[i];
        }
    }
    *resultado = minimo;
    return true;
}

bool copiar_texto(const char origen[], char destino[], size_t capacidad)
{
    if (origen == NULL || destino == NULL || capacidad == 0) {
        return false;
    }
    const size_t longitud = strlen(origen);
    if (longitud >= capacidad) {
        return false;
    }
    for (size_t i = 0; i < longitud; i++) {
        destino[i] = origen[i];
    }
    destino[longitud] = '\0';
    return true;
}

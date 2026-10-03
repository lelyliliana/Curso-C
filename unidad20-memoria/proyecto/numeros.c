#include "numeros.h"
#include <stdint.h>
#include <stdlib.h>
static bool forma_valida(const struct Numeros *lista) {
    return lista != NULL && lista->usados <= lista->capacidad &&
           lista->capacidad <= LIMITE_NUMEROS &&
           ((lista->capacidad == 0 && lista->datos == NULL) ||
            (lista->capacidad > 0 && lista->datos != NULL));
}
bool reservar_numeros(struct Numeros *lista, size_t capacidad) {
    if (!forma_valida(lista) || capacidad > SIZE_MAX / sizeof *lista->datos ||
        capacidad > LIMITE_NUMEROS) return false;
    if (capacidad <= lista->capacidad) return true;
    int *nuevo = realloc(lista->datos, capacidad * sizeof *lista->datos);
    if (nuevo == NULL) return false;
    lista->datos = nuevo;
    lista->capacidad = capacidad;
    return true;
}
bool agregar_numero(struct Numeros *lista, int valor) {
    if (!forma_valida(lista) || valor < 0 || valor > 100 ||
        lista->usados == LIMITE_NUMEROS) return false;
    if (lista->usados == lista->capacidad) {
        size_t nueva = lista->capacidad == 0 ? 2 : lista->capacidad * 2;
        if (nueva > LIMITE_NUMEROS) nueva = LIMITE_NUMEROS;
        if (!reservar_numeros(lista, nueva)) return false;
    }
    lista->datos[lista->usados] = valor;
    ++lista->usados;
    return true;
}
void liberar_numeros(struct Numeros *lista) {
    if (lista == NULL) return;
    free(lista->datos);
    lista->datos = NULL;
    lista->usados = 0;
    lista->capacidad = 0;
}

#include "numeros.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#ifdef NDEBUG
#error Estas pruebas requieren assert activo
#endif
int main(void) {
    struct Numeros lista = {0};
    bool ok = reservar_numeros(&lista, 0);
    assert(ok && lista.datos == NULL);
    for (size_t i = 0; i < LIMITE_NUMEROS; ++i) {
        ok = agregar_numero(&lista, (int)(i % 101));
        assert(ok && lista.usados == i + 1);
    }
    for (size_t i = 0; i < lista.usados; ++i) assert(lista.datos[i] == (int)(i % 101));
    int *antes = lista.datos;
    ok = agregar_numero(&lista, 10);
    assert(!ok && lista.datos == antes && lista.usados == LIMITE_NUMEROS);
    ok = reservar_numeros(&lista, SIZE_MAX);
    assert(!ok && lista.datos == antes);
    ok = agregar_numero(&lista, -1);
    assert(!ok);
    ok = agregar_numero(NULL, 0);
    assert(!ok);
    liberar_numeros(&lista);
    liberar_numeros(&lista);
    liberar_numeros(NULL);
    assert(lista.datos == NULL && lista.usados == 0 && lista.capacidad == 0);
    ok = agregar_numero(&lista, 100);
    assert(ok && lista.datos[0] == 100);
    liberar_numeros(&lista);
    puts("Pruebas de numeros: OK.");
    return 0;
}

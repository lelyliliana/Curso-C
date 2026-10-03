#include "filtro.h"
#include <assert.h>
#include <stdio.h>
#ifdef NDEBUG
#error "Las pruebas requieren assert activo."
#endif

int main(void)
{
    const int origen[] = {8, 2, 0, 10, 5};
    const int fuera[] = {8, 101};
    int destino[3] = {70, 71, 72};
    size_t usados = 99;
    bool ok = filtrar_minimo(origen, 5, 5, destino, 3, &usados);
    assert(ok && usados == 3);
    assert(destino[0] == 8 && destino[1] == 10 && destino[2] == 5);
    destino[0] = 70; destino[1] = 71; destino[2] = 72; usados = 99;
    ok = filtrar_minimo(origen, 5, 0, destino, 3, &usados);
    assert(!ok && usados == 99);
    assert(destino[0] == 70 && destino[1] == 71 && destino[2] == 72);
    ok = filtrar_minimo(fuera, 2, 5, destino, 3, &usados);
    assert(!ok && usados == 99 && destino[0] == 70);
    ok = filtrar_minimo(origen, 5, 101, NULL, 0, &usados);
    assert(ok && usados == 0);
    ok = filtrar_minimo(NULL, 0, 5, NULL, 0, &usados);
    assert(ok && usados == 0);
    ok = filtrar_minimo(NULL, 1, 5, destino, 3, &usados);
    assert(!ok && usados == 0);
    ok = filtrar_minimo(origen, 5, 5, NULL, 3, &usados);
    assert(!ok && usados == 0);
    ok = filtrar_minimo(origen, 5, 5, destino, 3, NULL);
    assert(!ok);
    puts("Pruebas de filtro: OK.");
    return 0;
}

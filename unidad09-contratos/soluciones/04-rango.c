#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef NDEBUG
#error "Estas pruebas requieren assert activo."
#endif

bool en_rango(int valor, int minimo, int maximo)
{
    return minimo <= maximo && valor >= minimo && valor <= maximo;
}

int main(void)
{
    assert(!en_rango(-1, 0, 100));
    assert(en_rango(0, 0, 100));
    assert(en_rango(100, 0, 100));
    assert(!en_rango(101, 0, 100));
    assert(!en_rango(5, 10, 0));
    printf("Pruebas de rango: OK.\n");
    return 0;
}

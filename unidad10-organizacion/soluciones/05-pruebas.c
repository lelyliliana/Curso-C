#include "recibo.h"

#include <assert.h>
#include <stdio.h>

#ifdef NDEBUG
#error "Estas pruebas requieren assert activo."
#endif

int main(void)
{
    assert(!cantidad_valida(-1));
    assert(cantidad_valida(0));
    assert(cantidad_valida(100));
    assert(!cantidad_valida(101));

    assert(subtotal_centavos(0) == 0);
    assert(subtotal_centavos(1) == 125);
    assert(subtotal_centavos(100) == 12500);

    assert(envio_centavos(0) == 0);
    assert(envio_centavos(1) == 500);
    assert(envio_centavos(9) == 500);
    assert(envio_centavos(10) == 500);
    assert(envio_centavos(19) == 500);
    assert(envio_centavos(20) == 0);
    assert(envio_centavos(100) == 0);

    assert(total_centavos(0) == 0);
    assert(total_centavos(1) == 625);
    assert(total_centavos(9) == 1625);
    assert(total_centavos(10) == 1750);
    assert(total_centavos(19) == 2875);
    assert(total_centavos(20) == 2500);
    assert(total_centavos(100) == 12500);

    printf("Pruebas de nueva regla: OK.\n");
    return 0;
}

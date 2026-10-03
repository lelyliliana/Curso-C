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
    assert(envio_centavos(10) == 0);
    assert(envio_centavos(100) == 0);

    assert(total_centavos(0) == 0);
    assert(total_centavos(1) == 625);
    assert(total_centavos(9) == 1625);
    assert(total_centavos(10) == 1250);
    assert(total_centavos(100) == 12500);

    printf("Pruebas del recibo: OK.\n");
    return 0;
}

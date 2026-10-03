#include "recibo.h"

bool cantidad_valida(int cantidad)
{
    return cantidad >= 0 && cantidad <= 100;
}

int subtotal_centavos(int cantidad)
{
    return cantidad * 125;
}

int envio_centavos(int cantidad)
{
    if (cantidad == 0 || cantidad >= 20) {
        return 0;
    }
    return 500;
}

int total_centavos(int cantidad)
{
    return subtotal_centavos(cantidad) + envio_centavos(cantidad);
}

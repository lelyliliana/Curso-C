#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
    if (cantidad == 0 || cantidad >= 10) {
        return 0;
    }
    return 500;
}

int total_centavos(int cantidad)
{
    return subtotal_centavos(cantidad) + envio_centavos(cantidad);
}

int main(void)
{
    int cantidad = 9;
    if (!cantidad_valida(cantidad)) {
        printf("Cantidad invalida.\n");
        return EXIT_FAILURE;
    }
    int total = total_centavos(cantidad);
    printf("Subtotal: %d centavos\n", subtotal_centavos(cantidad));
    printf("Envio: %d centavos\n", envio_centavos(cantidad));
    printf("Total: %d.%02d\n", total / 100, total % 100);
    return EXIT_SUCCESS;
}

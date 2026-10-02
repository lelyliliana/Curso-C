#include <stdio.h>

int main(void)
{
    int precio_centavos = 1250;
    int cantidad = 3;
    int envio_centavos = 500;
    int subtotal_centavos = precio_centavos * cantidad;
    int total_centavos = subtotal_centavos + envio_centavos;
    int unidades = total_centavos / 100;
    int centavos = total_centavos % 100;

    printf("Subtotal: %d centavos\n", subtotal_centavos);
    printf("Envio: %d centavos\n", envio_centavos);
    printf("Total: %d.%02d\n", unidades, centavos);
    return 0;
}

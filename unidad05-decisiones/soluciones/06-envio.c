#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int cantidad = 3;
    const int precio_centavos = 1250;

    if (cantidad < 0 || cantidad > 10) {
        printf("Cantidad invalida.\n");
        return EXIT_FAILURE;
    }

    int envio_centavos = 500;
    if (cantidad == 0 || cantidad >= 3) {
        envio_centavos = 0;
    }
    int total_centavos = precio_centavos * cantidad + envio_centavos;
    printf("Envio: %d centavos\n", envio_centavos);
    printf("Total: %d.%02d\n", total_centavos / 100, total_centavos % 100);
    return EXIT_SUCCESS;
}

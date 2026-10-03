#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Cantidad de 0 a 100, solo digitos (maximo 8).\n");
    int valor = 0;
    int longitud = 0;
    bool invalida = false;
    int c = getchar();

    while (c != '\n' && c != EOF) {
        if (longitud == 8) {
            invalida = true;
        } else {
            longitud++;
            if (c < '0' || c > '9') {
                invalida = true;
            } else if (!invalida) {
                int digito = c - '0';
                if (valor > 10 || (valor == 10 && digito > 0)) {
                    invalida = true;
                } else {
                    valor = valor * 10 + digito;
                }
            }
        }
        c = getchar();
    }

    if (ferror(stdin)) {
        printf("Error de lectura.\n");
        return EXIT_FAILURE;
    }
    if (longitud == 0 && c == EOF) {
        printf("Sin datos.\n");
        return EXIT_SUCCESS;
    }
    if (longitud == 0 || invalida) {
        printf("Entrada invalida.\n");
        return EXIT_FAILURE;
    }

    const int precio_centavos = 125;
    int envio_centavos = 500;
    if (valor == 0 || valor >= 10) {
        envio_centavos = 0;
    }
    int subtotal_centavos = precio_centavos * valor;
    int total_centavos = subtotal_centavos + envio_centavos;
    printf("Subtotal: %d centavos\n", subtotal_centavos);
    printf("Envio: %d centavos\n", envio_centavos);
    printf("Total: %d.%02d\n", total_centavos / 100, total_centavos % 100);
    return EXIT_SUCCESS;
}

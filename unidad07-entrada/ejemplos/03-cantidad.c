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
    printf("Cantidad: %d\n", valor);
    return EXIT_SUCCESS;
}

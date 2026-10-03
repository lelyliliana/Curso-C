#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum ResultadoLectura {
    LECTURA_INVALIDA = -1,
    LECTURA_FIN = -2,
    LECTURA_ERROR = -3
};

int leer_cantidad(void)
{
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
        return LECTURA_ERROR;
    }
    if (longitud == 0 && c == EOF) {
        return LECTURA_FIN;
    }
    if (longitud == 0 || invalida) {
        return LECTURA_INVALIDA;
    }
    return valor;
}

int main(void)
{
    int suma = 0;
    for (int numero = 1; numero <= 2; numero++) {
        printf("Cantidad %d de 0 a 100, solo digitos (maximo 8).\n", numero);
        int resultado = leer_cantidad();
        if (resultado == LECTURA_FIN) {
            printf("Fin antes de completar dos cantidades.\n");
            return EXIT_FAILURE;
        }
        if (resultado == LECTURA_ERROR) {
            printf("Error de lectura.\n");
            return EXIT_FAILURE;
        }
        if (resultado == LECTURA_INVALIDA) {
            printf("Entrada invalida.\n");
            return EXIT_FAILURE;
        }
        suma += resultado;
    }
    printf("Suma de cantidades: %d\n", suma);
    return EXIT_SUCCESS;
}

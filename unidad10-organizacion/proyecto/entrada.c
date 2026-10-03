#include "entrada.h"

#include <stdbool.h>
#include <stdio.h>

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

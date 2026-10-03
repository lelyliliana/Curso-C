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

void mostrar_recibo(int cantidad)
{
    int subtotal = subtotal_centavos(cantidad);
    int envio = envio_centavos(cantidad);
    int total = total_centavos(cantidad);
    printf("Subtotal: %d centavos\n", subtotal);
    printf("Envio: %d centavos\n", envio);
    printf("Total: %d.%02d\n", total / 100, total % 100);
}

int main(void)
{
    printf("Cantidad de 0 a 100, solo digitos (maximo 8).\n");
    int resultado = leer_cantidad();

    if (resultado == LECTURA_FIN) {
        printf("Sin datos.\n");
        return EXIT_SUCCESS;
    }
    if (resultado == LECTURA_ERROR) {
        printf("Error de lectura.\n");
        return EXIT_FAILURE;
    }
    if (resultado == LECTURA_INVALIDA) {
        printf("Entrada invalida.\n");
        return EXIT_FAILURE;
    }
    if (!cantidad_valida(resultado)) {
        printf("Resultado del lector fuera del contrato.\n");
        return EXIT_FAILURE;
    }

    mostrar_recibo(resultado);
    return EXIT_SUCCESS;
}

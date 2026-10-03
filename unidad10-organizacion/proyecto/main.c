#include "entrada.h"
#include "recibo.h"

#include <stdio.h>
#include <stdlib.h>

static void mostrar_recibo(int cantidad)
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

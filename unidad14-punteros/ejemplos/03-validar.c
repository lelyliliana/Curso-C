#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool descontar_uno(int *cantidad)
{
    if (cantidad == NULL) {
        return false;
    }
    if (*cantidad < 1 || *cantidad > 100) {
        return false;
    }
    *cantidad -= 1;
    return true;
}

int main(void)
{
    int cantidad = 1;
    if (descontar_uno(&cantidad)) {
        printf("Descuento valido: %d\n", cantidad);
    }
    if (!descontar_uno(&cantidad)) {
        printf("Sin descuento; conserva %d.\n", cantidad);
    }
    if (!descontar_uno(NULL)) {
        puts("Puntero nulo rechazado.");
    }
    return 0;
}

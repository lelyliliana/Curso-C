#include <stdio.h>

int main(void)
{
    int existencias = 15;
    int registro_anterior = existencias;

    existencias = 11;
    printf("Registro anterior: %d\n", registro_anterior);
    printf("Existencias actuales: %d\n", existencias);
    registro_anterior = existencias;
    printf("Registro actualizado: %d\n", registro_anterior);
    return 0;
}

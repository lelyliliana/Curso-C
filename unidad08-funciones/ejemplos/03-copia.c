#include <stdio.h>

void cambiar_copia(int numero)
{
    numero = 9;
    printf("Dentro: %d\n", numero);
}

int main(void)
{
    int numero = 12;

    cambiar_copia(numero);
    printf("En main: %d\n", numero);
    return 0;
}

#include <stdio.h>

int main(void)
{
    int cantidad = 12;
    int *acceso = &cantidad;
    printf("Valor: %d\n", cantidad);
    printf("Direccion: %p\n", (void *)acceso);
    printf("Por puntero: %d\n", *acceso);
    *acceso = 9;
    printf("Despues: %d\n", cantidad);
    return 0;
}

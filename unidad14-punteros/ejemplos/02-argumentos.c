#include <stdio.h>

void cambiar_copia(int valor)
{
    valor = 9;
    printf("Copia local: %d\n", valor);
}

void cambiar_objeto(int *acceso)
{
    *acceso = 9;
    acceso = NULL;
}

int main(void)
{
    int cantidad = 12;
    int *acceso = &cantidad;
    cambiar_copia(cantidad);
    printf("Tras copia: %d\n", cantidad);
    cambiar_objeto(acceso);
    printf("Tras acceso: %d\n", cantidad);
    if (acceso == &cantidad) {
        puts("El puntero del llamador conserva su direccion.");
    }
    return 0;
}

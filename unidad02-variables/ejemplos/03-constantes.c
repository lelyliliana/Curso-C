#include <stdio.h>

int main(void)
{
    const int capacidad = 20;
    int ocupados = 12;

    printf("Capacidad: %d\n", capacidad);
    printf("Ocupados: %d\n", ocupados);
    ocupados = 9;
    printf("Ocupados ahora: %d\n", ocupados);
    return 0;
}

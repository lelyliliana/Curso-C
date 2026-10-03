#include <stdio.h>

int main(void)
{
    const int capacidad = 20;
    int ocupados = 12;

    if (ocupados < capacidad) {
        printf("Hay plazas disponibles.\n");
        printf("Plazas: %d\n", capacidad - ocupados);
    } else {
        printf("Sala completa.\n");
    }
    return 0;
}

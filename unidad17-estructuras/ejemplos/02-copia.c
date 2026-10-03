#include "../proyecto/sensor.h"
#include <stdio.h>
static void cambiar_copia(struct Sensor sensor)
{
    sensor.valor = 99;
    printf("Copia en funcion: %d\n", sensor.valor);
}
int main(void)
{
    struct Sensor original = {.nombre = "patio", .valor = 25};
    struct Sensor copia = original;
    copia.nombre[0] = 'P';
    copia.valor = 40;
    cambiar_copia(original);
    printf("Original: %s %d\nCopia: %s %d\n", original.nombre, original.valor, copia.nombre, copia.valor);
    return 0;
}

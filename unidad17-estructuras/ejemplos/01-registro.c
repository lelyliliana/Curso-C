#include "../proyecto/sensor.h"
#include <stdio.h>
int main(void)
{
    struct Sensor sensor = {.nombre = "patio", .valor = 25};
    printf("Nombre: %s\nValor: %d\n", sensor.nombre, sensor.valor);
    sensor.valor = 30;
    printf("Actualizado: %d\n", sensor.valor);
    return 0;
}

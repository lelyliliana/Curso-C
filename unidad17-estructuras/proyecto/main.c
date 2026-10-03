#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    struct Sensor sensor = {0};
    if (!crear_sensor("sensor_2", 0, &sensor)) {
        puts("Registro rechazado.");
        return EXIT_FAILURE;
    }
    printf("Creado: %s %d\n", sensor.nombre, sensor.valor);
    if (!crear_sensor("nombre demasiado largo", 25, &sensor)) {
        printf("Rechazo; conserva %s %d.\n", sensor.nombre, sensor.valor);
    }
    return EXIT_SUCCESS;
}

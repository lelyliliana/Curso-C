#include "../proyecto/sensor.h"
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    const struct Sensor sensores[] = {{"patio", 25}, {"salon", 0}, {"taller", 100}};
    const size_t cantidad = sizeof sensores / sizeof sensores[0];
    int total = 0;
    for (size_t i = 0; i < cantidad; i++) {
        if (!sensor_valido(&sensores[i])) {
            puts("Registro invalido.");
            return EXIT_FAILURE;
        }
        total += sensores[i].valor;
    }
    for (size_t i = 0; i < cantidad; i++) {
        printf("%s: %d\n", sensores[i].nombre, sensores[i].valor);
    }
    printf("Total: %d\n", total);
    return EXIT_SUCCESS;
}

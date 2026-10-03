#include "sensor.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef NDEBUG
#error "Las pruebas requieren assert activo."
#endif
int main(void)
{
    struct Sensor sensor = {"previo", 77};
    bool ok = crear_sensor("abcdefghijkl", 100, &sensor);
    assert(ok && sensor_valido(&sensor));
    ok = crear_sensor("abcdefghijklm", 50, &sensor);
    assert(!ok && strcmp(sensor.nombre, "abcdefghijkl") == 0 && sensor.valor == 100);
    ok = crear_sensor("", 0, &sensor);
    assert(!ok && sensor.valor == 100);
    ok = crear_sensor("A", 101, &sensor);
    assert(!ok && sensor.valor == 100);
    struct Sensor sin_fin = {0};
    for (size_t i = 0; i < NOMBRE_SENSOR; i++) {sin_fin.nombre[i] = 'A';}
    assert(!sensor_valido(&sin_fin));
    assert(!sensor_valido(NULL));
    puts("Pruebas de sensor: OK.");
    return 0;
}

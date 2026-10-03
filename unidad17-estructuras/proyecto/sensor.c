#include "sensor.h"

static bool simbolo_valido(char simbolo)
{
    const char permitidos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";
    for (size_t i = 0; i < sizeof permitidos - 1; i++) {
        if (simbolo == permitidos[i]) {
            return true;
        }
    }
    return false;
}

bool sensor_valido(const struct Sensor *sensor)
{
    if (sensor == NULL || sensor->valor < 0 || sensor->valor > 100) {
        return false;
    }
    size_t i = 0;
    while (i < NOMBRE_SENSOR && sensor->nombre[i] != '\0') {
        if (!simbolo_valido(sensor->nombre[i])) {
            return false;
        }
        i++;
    }
    return i > 0 && i < NOMBRE_SENSOR;
}

bool crear_sensor(const char *nombre, int valor, struct Sensor *destino)
{
    if (nombre == NULL || destino == NULL || valor < 0 || valor > 100) {
        return false;
    }
    struct Sensor temporal = {0};
    size_t i = 0;
    while (nombre[i] != '\0') {
        if (i >= NOMBRE_SENSOR - 1 || !simbolo_valido(nombre[i])) {
            return false;
        }
        temporal.nombre[i] = nombre[i];
        i++;
    }
    if (i == 0) {
        return false;
    }
    temporal.nombre[i] = '\0';
    temporal.valor = valor;
    *destino = temporal;
    return true;
}

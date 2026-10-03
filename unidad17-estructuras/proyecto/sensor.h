#ifndef CURSO_C_SENSOR_H
#define CURSO_C_SENSOR_H
#include <stdbool.h>
#include <stddef.h>
enum { NOMBRE_SENSOR = 13 };
struct Sensor {
    char nombre[NOMBRE_SENSOR];
    int valor;
};
/* sensor apunta a un registro vivo legible; NULL se rechaza.
   Comprueba terminador dentro del miembro, nombre no vacio (1..12),
   simbolos A-Z/a-z/0-9/_/- y valor 0..100. */
bool sensor_valido(const struct Sensor *sensor);
/* destino es registro vivo modificable, separado de nombre.
   nombre es cadena terminada. false conserva destino completo. */
bool crear_sensor(const char *nombre, int valor, struct Sensor *destino);
#endif

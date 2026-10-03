#include "entrada.h"
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const char *saltar_blancos(const char *posicion)
{
    while (*posicion == ' ' || *posicion == '\t') {
        posicion++;
    }
    return posicion;
}

static const char *saltar_digitos(const char *posicion)
{
    while (*posicion >= '0' && *posicion <= '9') {
        posicion++;
    }
    return posicion;
}

static bool sintaxis_numero(const char *texto, bool decimal)
{
    const char *posicion = saltar_blancos(texto);
    if (*posicion == '+' || *posicion == '-') {
        posicion++;
    }
    const char *inicio = posicion;
    posicion = saltar_digitos(posicion);
    if (posicion == inicio) {
        return false;
    }
    if (decimal && *posicion == '.') {
        posicion++;
        inicio = posicion;
        posicion = saltar_digitos(posicion);
        if (posicion == inicio) {
            return false;
        }
    }
    if (decimal && (*posicion == 'e' || *posicion == 'E')) {
        posicion++;
        if (*posicion == '+' || *posicion == '-') {
            posicion++;
        }
        inicio = posicion;
        posicion = saltar_digitos(posicion);
        if (posicion == inicio) {
            return false;
        }
    }
    return *saltar_blancos(posicion) == '\0';
}

enum EstadoLinea leer_linea(char destino[], size_t capacidad)
{
    if (destino == NULL || capacidad == 0) {
        return LINEA_ARGUMENTO;
    }
    destino[0] = '\0';
    size_t usados = 0;
    bool hubo_datos = false;
    bool larga = false;
    bool invalida = false;
    int byte;
    while ((byte = getchar()) != '\n' && byte != EOF) {
        hubo_datos = true;
        if (byte == '\0' || byte > CHAR_MAX) {
            invalida = true;
        } else if (usados >= capacidad - 1) {
            larga = true;
        } else if (!invalida && !larga) {
            destino[usados] = (char)byte;
            usados++;
        }
    }
    if (ferror(stdin)) {
        destino[0] = '\0';
        return LINEA_ERROR;
    }
    if (byte == EOF && !hubo_datos) {
        return LINEA_FIN;
    }
    if (invalida) {
        destino[0] = '\0';
        return LINEA_INVALIDA;
    }
    if (larga) {
        destino[0] = '\0';
        return LINEA_LARGA;
    }
    destino[usados] = '\0';
    return LINEA_OK;
}

bool convertir_entero(const char texto[], int minimo, int maximo, int *resultado)
{
    if (texto == NULL || resultado == NULL || minimo > maximo
        || !sintaxis_numero(texto, false)) {
        return false;
    }
    char *fin = NULL;
    errno = 0;
    const long valor = strtol(texto, &fin, 10);
    if (errno == ERANGE || fin == texto || *saltar_blancos(fin) != '\0'
        || valor < minimo || valor > maximo) {
        return false;
    }
    *resultado = (int)valor;
    return true;
}

bool convertir_decimal(const char texto[], double minimo, double maximo, double *resultado)
{
    if (texto == NULL || resultado == NULL || !isfinite(minimo) || !isfinite(maximo)
        || minimo > maximo || !sintaxis_numero(texto, true)) {
        return false;
    }
    char *fin = NULL;
    errno = 0;
    const double valor = strtod(texto, &fin);
    if (errno == ERANGE || fin == texto || *saltar_blancos(fin) != '\0'
        || !isfinite(valor) || valor < minimo || valor > maximo) {
        return false;
    }
    *resultado = valor;
    return true;
}

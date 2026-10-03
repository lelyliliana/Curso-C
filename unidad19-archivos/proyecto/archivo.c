#include "archivo.h"
#include "../../unidad16-lineas/proyecto/entrada.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

enum LineaArchivo {TEXTO_OK, TEXTO_FIN, TEXTO_INVALIDO, TEXTO_IO};
static enum LineaArchivo leer_texto(FILE *flujo, char texto[], size_t capacidad)
{
    size_t usados = 0;
    bool hubo = false;
    bool invalido = false;
    int byte;
    texto[0] = '\0';
    while ((byte = fgetc(flujo)) != '\n' && byte != EOF) {
        hubo = true;
        if (byte == 0 || byte > CHAR_MAX || usados >= capacidad - 1) {
            invalido = true;
        } else if (!invalido) {
            texto[usados++] = (char)byte;
        }
    }
    if (ferror(flujo)) {return TEXTO_IO;}
    if (byte == EOF && !hubo) {return TEXTO_FIN;}
    if (invalido) {return TEXTO_INVALIDO;}
    texto[usados] = '\0';
    return TEXTO_OK;
}

static enum ResultadoArchivo leer_contenido(FILE *flujo, struct Sensor temporal[], size_t capacidad, size_t *cantidad)
{
    char linea[33];
    enum LineaArchivo estado = leer_texto(flujo, linea, sizeof linea);
    if (estado == TEXTO_IO) {return ARCHIVO_IO;}
    if (estado != TEXTO_OK || strcmp(linea, "C-REG-1") != 0) {return ARCHIVO_FORMATO;}
    estado = leer_texto(flujo, linea, sizeof linea);
    if (estado == TEXTO_IO) {return ARCHIVO_IO;}
    if (estado != TEXTO_OK || linea[0] < '0' || linea[0] > '3' || linea[1] != '\0') {
        return ARCHIVO_FORMATO;
    }
    const size_t n = (size_t)(linea[0] - '0');
    if (n > capacidad) {return ARCHIVO_CAPACIDAD;}
    for (size_t i = 0; i < n; i++) {
        estado = leer_texto(flujo, linea, sizeof linea);
        if (estado == TEXTO_IO) {return ARCHIVO_IO;}
        if (estado != TEXTO_OK) {return ARCHIVO_FORMATO;}
        char *separador = strchr(linea, ';');
        if (separador == NULL) {return ARCHIVO_FORMATO;}
        *separador = '\0';
        const char *numero = separador + 1;
        if (*numero == '\0') {return ARCHIVO_FORMATO;}
        for (const char *p = numero; *p != '\0'; p++) {
            if (*p < '0' || *p > '9') {return ARCHIVO_FORMATO;}
        }
        int valor = 0;
        if (!convertir_entero(numero, 0, 100, &valor) || !crear_sensor(linea, valor, &temporal[i])) {
            return ARCHIVO_FORMATO;
        }
    }
    const int siguiente = fgetc(flujo);
    if (ferror(flujo)) {return ARCHIVO_IO;}
    if (siguiente != EOF) {return ARCHIVO_FORMATO;}
    *cantidad = n;
    return ARCHIVO_OK;
}

enum ResultadoArchivo guardar_registros(const char *ruta, const struct Sensor datos[], size_t cantidad)
{
    if (ruta == NULL || cantidad > 3 || (cantidad > 0 && datos == NULL)) {return ARCHIVO_ARGUMENTO;}
    for (size_t i = 0; i < cantidad; i++) {
        if (!sensor_valido(&datos[i])) {return ARCHIVO_FORMATO;}
    }
    FILE *flujo = fopen(ruta, "wx");
    if (flujo == NULL) {return ARCHIVO_ABRIR;}
    enum ResultadoArchivo resultado = ARCHIVO_OK;
    if (fprintf(flujo, "C-REG-1\n%zu\n", cantidad) < 0) {resultado = ARCHIVO_IO;}
    for (size_t i = 0; i < cantidad && resultado == ARCHIVO_OK; i++) {
        if (fprintf(flujo, "%s;%d\n", datos[i].nombre, datos[i].valor) < 0) {resultado = ARCHIVO_IO;}
    }
    if (fclose(flujo) == EOF) {resultado = ARCHIVO_IO;}
    return resultado;
}

enum ResultadoArchivo cargar_registros(const char *ruta, struct Sensor destino[], size_t capacidad, size_t *usados)
{
    if (ruta == NULL || usados == NULL || (capacidad > 0 && destino == NULL)) {return ARCHIVO_ARGUMENTO;}
    FILE *flujo = fopen(ruta, "r");
    if (flujo == NULL) {return ARCHIVO_ABRIR;}
    struct Sensor temporal[3] = {0};
    size_t cantidad = 0;
    enum ResultadoArchivo resultado = leer_contenido(flujo, temporal, capacidad, &cantidad);
    if (fclose(flujo) == EOF) {resultado = ARCHIVO_IO;}
    if (resultado != ARCHIVO_OK) {return resultado;}
    for (size_t i = 0; i < cantidad; i++) {destino[i] = temporal[i];}
    *usados = cantidad;
    return ARCHIVO_OK;
}

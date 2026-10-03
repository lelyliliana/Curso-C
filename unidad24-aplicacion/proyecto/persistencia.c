#include "persistencia.h"
#include "../../unidad16-lineas/proyecto/entrada.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
enum LineaPersistencia { P_LINEA, P_FIN, P_INVALIDA, P_IO };
static enum LineaPersistencia linea_archivo(FILE *f, char texto[33]) {
    size_t usados = 0;
    bool hubo = false, invalida = false;
    int byte;
    while ((byte = fgetc(f)) != '\n' && byte != EOF) {
        hubo = true;
        if (byte == 0 || byte > CHAR_MAX || usados == 32) invalida = true;
        else if (!invalida) texto[usados++] = (char)byte;
    }
    texto[usados] = '\0';
    if (ferror(f)) return P_IO;
    if (byte == EOF && !hubo) return P_FIN;
    return invalida ? P_INVALIDA : P_LINEA;
}
static bool entero_archivo(const char *texto, int *salida) {
    if (*texto == '\0') return false;
    for (const char *p = texto; *p != '\0'; ++p)
        if (*p < '0' || *p > '9') return false;
    return convertir_entero(texto, 0, 100, salida);
}
static enum ResultadoPersistencia contenido(FILE *f, struct Catalogo *temporal) {
    char linea[33];
    enum LineaPersistencia e = linea_archivo(f, linea);
    if (e == P_IO) return PERSISTE_IO;
    if (e != P_LINEA || strcmp(linea, "C-AGENDA-1") != 0) return PERSISTE_FORMATO;
    e = linea_archivo(f, linea);
    if (e == P_IO) return PERSISTE_IO;
    int cantidad = 0;
    if (e != P_LINEA || !entero_archivo(linea, &cantidad)) return PERSISTE_FORMATO;
    for (int i = 0; i < cantidad; ++i) {
        e = linea_archivo(f, linea);
        if (e == P_IO) return PERSISTE_IO;
        if (e != P_LINEA) return PERSISTE_FORMATO;
        char *sep = strchr(linea, ';');
        if (sep == NULL) return PERSISTE_FORMATO;
        *sep = '\0';
        int valor = 0;
        if (!entero_archivo(sep + 1, &valor)) return PERSISTE_FORMATO;
        enum ResultadoAgenda r = insertar_sensor(temporal, linea, valor);
        if (r == AGENDA_MEMORIA) return PERSISTE_MEMORIA;
        if (r != AGENDA_OK) return PERSISTE_FORMATO;
    }
    int byte = fgetc(f);
    if (ferror(f)) return PERSISTE_IO;
    return byte == EOF ? PERSISTE_OK : PERSISTE_FORMATO;
}
enum ResultadoPersistencia guardar_agenda(const char *ruta, const struct Catalogo *agenda) {
    if (ruta == NULL || !agenda_valida(agenda)) return PERSISTE_ARGUMENTO;
    FILE *f = fopen(ruta, "wx");
    if (f == NULL) return PERSISTE_ABRIR;
    enum ResultadoPersistencia r = PERSISTE_OK;
    if (fprintf(f, "C-AGENDA-1\n%zu\n", agenda->usados) < 0) r = PERSISTE_IO;
    for (size_t i = 0; i < agenda->usados && r == PERSISTE_OK; ++i)
        if (fprintf(f, "%s;%d\n", agenda->datos[i].nombre, agenda->datos[i].valor) < 0) r = PERSISTE_IO;
    if (fclose(f) == EOF) r = PERSISTE_IO;
    return r;
}
enum ResultadoPersistencia cargar_agenda(const char *ruta, struct Catalogo *destino) {
    if (ruta == NULL || !agenda_valida(destino)) return PERSISTE_ARGUMENTO;
    FILE *f = fopen(ruta, "r");
    if (f == NULL) return PERSISTE_ABRIR;
    struct Catalogo temporal = {0};
    enum ResultadoPersistencia r = contenido(f, &temporal);
    if (fclose(f) == EOF) r = PERSISTE_IO;
    if (r == PERSISTE_OK && !mover_catalogo(&temporal, destino)) r = PERSISTE_ARGUMENTO;
    liberar_catalogo(&temporal);
    return r;
}

#include "persistencia.h"
#include "../../unidad16-lineas/proyecto/entrada.h"
#include <stdio.h>
#include <stdlib.h>
/* Entrada invalida cancela esa operacion; fin/error termina la sesion. */
static enum EstadoLinea pedir_texto(const char *mensaje, char *texto, size_t capacidad) {
    puts(mensaje);
    return leer_linea(texto, capacidad);
}
static bool termina(enum EstadoLinea e) {return e == LINEA_FIN || e == LINEA_ERROR || e == LINEA_ARGUMENTO;}
static void listar(const struct Catalogo *a) {
    printf("Registros: %zu\n", a->usados);
    for (size_t i = 0; i < a->usados; ++i) printf("%s: %d\n", a->datos[i].nombre, a->datos[i].valor);
}
int main(void) {
    struct Catalogo agenda = {0};
    char texto[129], nombre[13];
    int salida = EXIT_SUCCESS;
    bool seguir = true;
    while (seguir) {
        puts("0 salir | 1 agregar | 2 listar | 3 buscar | 4 actualizar | 5 quitar | 6 resumen | 7 guardar | 8 cargar");
        enum EstadoLinea e = leer_linea(texto, sizeof texto);
        if (termina(e)) {
            fputs("Entrada terminada; cambios no guardados pueden perderse.\n", stderr);
            salida = EXIT_FAILURE; break;
        }
        int opcion = 0;
        if (e != LINEA_OK || !convertir_entero(texto, 0, 8, &opcion)) {puts("Opcion invalida."); continue;}
        if (opcion == 0) {puts("Sesion terminada; guarda antes de salir si deseas conservar cambios."); seguir = false; continue;}
        if (opcion == 2) {listar(&agenda); continue;}
        if (opcion == 6) {
            struct ResumenAgenda r;
            if (!resumir_agenda(&agenda, &r)) puts("Agenda vacia; no hay media.");
            else printf("Cantidad: %zu; total: %lu; minimo: %d; maximo: %d; media: %.2f\n", r.cantidad, r.total, r.minimo, r.maximo, r.media);
            continue;
        }
        if (opcion == 7 || opcion == 8) {
            e = pedir_texto("Ruta (1..128 bytes):", texto, sizeof texto);
            if (termina(e)) {salida = EXIT_FAILURE; break;}
            if (e != LINEA_OK || texto[0] == '\0') {puts("Ruta invalida."); continue;}
            enum ResultadoPersistencia r = opcion == 7 ? guardar_agenda(texto, &agenda) : cargar_agenda(texto, &agenda);
            if (r == PERSISTE_OK) puts(opcion == 7 ? "Guardado completo." : "Carga completa.");
            else printf("Archivo rechazado (%d).\n", (int)r);
            continue;
        }
        e = pedir_texto("Nombre (1..12, letras/digitos/_/-):", nombre, sizeof nombre);
        if (termina(e)) {salida = EXIT_FAILURE; break;}
        struct Sensor comprobacion;
        if (e != LINEA_OK || !crear_sensor(nombre, 0, &comprobacion)) {puts("Nombre invalido."); continue;}
        if (opcion == 3) {
            size_t posicion = 0;
            if (buscar_sensor(&agenda, nombre, &posicion)) printf("%s: %d\n", agenda.datos[posicion].nombre, agenda.datos[posicion].valor);
            else puts("No encontrado.");
            continue;
        }
        enum ResultadoAgenda r;
        if (opcion == 5) r = quitar_sensor(&agenda, nombre);
        else {
            e = pedir_texto("Valor (0..100):", texto, sizeof texto);
            if (termina(e)) {salida = EXIT_FAILURE; break;}
            int valor = 0;
            if (e != LINEA_OK || !convertir_entero(texto, 0, 100, &valor)) {puts("Valor invalido."); continue;}
            r = opcion == 1 ? insertar_sensor(&agenda, nombre, valor) : actualizar_sensor(&agenda, nombre, valor);
        }
        if (r == AGENDA_MEMORIA) {fputs("Sin memoria; agenda conservada.\n", stderr); salida = EXIT_FAILURE; break;}
        if (r == AGENDA_OK) puts("Operacion completa.");
        else printf("Operacion rechazada (%d).\n", (int)r);
    }
    liberar_catalogo(&agenda);
    return salida;
}

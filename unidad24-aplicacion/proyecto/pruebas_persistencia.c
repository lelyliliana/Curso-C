#include "persistencia.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef NDEBUG
#error Estas pruebas requieren assert activo
#endif
int main(int argc, char *argv[]) {
    if (argc != 2) return EXIT_FAILURE;
    struct Catalogo origen = {0}, destino = {0};
    enum ResultadoAgenda a = insertar_sensor(&origen, "A", 0); assert(a == AGENDA_OK);
    a = insertar_sensor(&origen, "B", 100); assert(a == AGENDA_OK);
    enum ResultadoPersistencia r = guardar_agenda(argv[1], &origen);
    if (r != PERSISTE_OK) {liberar_catalogo(&origen); return EXIT_FAILURE;}
    r = guardar_agenda(argv[1], &origen); assert(r == PERSISTE_ABRIR);
    a = insertar_sensor(&destino, "old", 77); assert(a == AGENDA_OK);
    r = cargar_agenda(argv[1], &destino);
    assert(r == PERSISTE_OK && destino.usados == 2 && strcmp(destino.datos[0].nombre, "A") == 0 && destino.datos[1].valor == 100);
    r = cargar_agenda(NULL, &destino); assert(r == PERSISTE_ARGUMENTO && destino.usados == 2);
    liberar_catalogo(&origen); liberar_catalogo(&destino);
    int retirado = remove(argv[1]); assert(retirado == 0);
    puts("Pruebas de persistencia: OK.");
    return EXIT_SUCCESS;
}

#include "archivo.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef NDEBUG
#error "Las pruebas requieren assert activo."
#endif
int main(int argc, char *argv[])
{
    if (argc != 2) {puts("Uso: pruebas_archivo ruta_nueva"); return EXIT_FAILURE;}
    FILE *temporal = tmpfile();
    if (temporal == NULL) {puts("No se pudo crear temporal."); return EXIT_FAILURE;}
    int escrito = fputs("abc\n", temporal);
    assert(escrito != EOF);
    int reposicion = fseek(temporal, 0, SEEK_SET);
    assert(reposicion == 0);
    int primero = fgetc(temporal);
    assert(primero == 'a');
    int cierre = fclose(temporal);
    assert(cierre == 0);
    struct Sensor destino = {"previo", 77};
    size_t usados = 99;
    enum ResultadoArchivo resultado = cargar_registros(NULL, &destino, 1, &usados);
    assert(resultado == ARCHIVO_ARGUMENTO && usados == 99 && destino.valor == 77);
    resultado = guardar_registros(NULL, &destino, 1);
    assert(resultado == ARCHIVO_ARGUMENTO);
    assert(strcmp(destino.nombre, "previo") == 0);
    const struct Sensor origen[] = {{"patio", 25}, {"salon", 0}};
    resultado = guardar_registros(argv[1], origen, 2);
    if (resultado != ARCHIVO_OK) {puts("No se pudo crear archivo nuevo de prueba."); return EXIT_FAILURE;}
    struct Sensor copia[3] = {0};
    resultado = cargar_registros(argv[1], copia, 3, &usados);
    assert(resultado == ARCHIVO_OK && usados == 2);
    assert(strcmp(copia[0].nombre, "patio") == 0 && copia[0].valor == 25);
    assert(strcmp(copia[1].nombre, "salon") == 0 && copia[1].valor == 0);
    resultado = guardar_registros(argv[1], origen, 2);
    assert(resultado == ARCHIVO_ABRIR);
    usados = 99;
    resultado = cargar_registros(argv[1], &destino, 1, &usados);
    assert(resultado == ARCHIVO_CAPACIDAD && usados == 99 && destino.valor == 77);
    int borrado = remove(argv[1]);
    if (borrado != 0) {puts("No se pudo retirar el archivo propio de prueba."); return EXIT_FAILURE;}
    puts("Pruebas de archivo: OK.");
    return 0;
}

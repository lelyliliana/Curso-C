#include "coleccion.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#ifdef NDEBUG
#error "Las pruebas requieren assert activo."
#endif

int main(void)
{
    const int datos[] = {8, 2, 0, 10, 5};
    const int fuera[] = {1, 101};
    int resultado = 77;
    bool ok = sumar_lecturas(datos, 5, &resultado);
    assert(ok && resultado == 25);
    ok = minimo_lecturas(datos, 5, &resultado);
    assert(ok && resultado == 0);
    ok = sumar_lecturas(NULL, 0, &resultado);
    assert(ok && resultado == 0);
    resultado = 77;
    ok = minimo_lecturas(NULL, 0, &resultado);
    assert(!ok && resultado == 77);
    ok = sumar_lecturas(fuera, 2, &resultado);
    assert(!ok && resultado == 77);
    ok = sumar_lecturas(NULL, 1, &resultado);
    assert(!ok && resultado == 77);
    ok = sumar_lecturas(datos, 6, &resultado);
    assert(!ok && resultado == 77);
    ok = minimo_lecturas(datos, 5, NULL);
    assert(!ok);
    char destino[6] = "viejo";
    ok = copiar_texto("abcde", destino, sizeof destino);
    assert(ok && strcmp(destino, "abcde") == 0);
    ok = copiar_texto("abcdef", destino, sizeof destino);
    assert(!ok && strcmp(destino, "abcde") == 0);
    ok = copiar_texto("", destino, sizeof destino);
    assert(ok && destino[0] == '\0');
    ok = copiar_texto(NULL, destino, sizeof destino);
    assert(!ok && destino[0] == '\0');
    puts("Pruebas de coleccion: OK.");
    return 0;
}

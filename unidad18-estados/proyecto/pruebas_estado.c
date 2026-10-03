#include "estado.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#ifdef NDEBUG
#error "Las pruebas requieren assert activo."
#endif
int main(void)
{
    enum Estado estado = APAGADO;
    bool ok = transicionar(&estado, INICIAR);
    assert(!ok && estado == APAGADO);
    ok = transicionar(&estado, ENCENDER); assert(ok && estado == LISTO);
    ok = transicionar(&estado, INICIAR); assert(ok && estado == ACTIVO);
    ok = transicionar(&estado, DETENER); assert(ok && estado == LISTO);
    ok = transicionar(&estado, ERROR_DETECTADO); assert(ok && estado == FALLO);
    ok = transicionar(&estado, RESTABLECER); assert(ok && estado == APAGADO);
    ok = transicionar(&estado, (enum Evento)99); assert(!ok && estado == APAGADO);
    ok = transicionar(NULL, ENCENDER); assert(!ok);
    puts("Pruebas de estado: OK.");
    return 0;
}

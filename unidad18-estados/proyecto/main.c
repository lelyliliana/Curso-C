#include "estado.h"
#include <stddef.h>
#include <stdio.h>
int main(void)
{
    enum Estado estado = APAGADO;
    const enum Evento eventos[] = {INICIAR, ENCENDER, INICIAR, ERROR_DETECTADO, INICIAR, RESTABLECER};
    for (size_t i = 0; i < sizeof eventos / sizeof eventos[0]; i++) {
        bool ok = transicionar(&estado, eventos[i]);
        printf("Evento %d: %s; estado %s\n", (int)eventos[i], ok ? "aceptado" : "rechazado", nombre_estado(estado));
    }
    return 0;
}

#include "../proyecto/estado.h"
#include <stddef.h>
#include <stdio.h>
int main(void)
{
    enum Estado estado = APAGADO;
    const enum Evento eventos[] = {ENCENDER, INICIAR, INICIAR, DETENER, RESTABLECER};
    size_t aceptados = 0;
    size_t rechazados = 0;
    for (size_t i = 0; i < sizeof eventos / sizeof eventos[0]; i++) {
        if (transicionar(&estado, eventos[i])) {aceptados++;} else {rechazados++;}
    }
    printf("Aceptados: %zu\nRechazados: %zu\nFinal: %s\n", aceptados, rechazados, nombre_estado(estado));
    return 0;
}

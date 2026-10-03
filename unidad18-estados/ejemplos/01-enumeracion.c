#include "../proyecto/estado.h"
#include <stdio.h>
int main(void)
{
    enum Estado estado = LISTO;
    printf("Nombre: %s\nCodigo: %d\n", nombre_estado(estado), (int)estado);
    printf("Codigo ajeno: %s\n", nombre_estado((enum Estado)99));
    return 0;
}

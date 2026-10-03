#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int objetos = 17;
    int por_caja = 5;

    if (objetos < 0 || objetos > 100 || por_caja < 1 || por_caja > 100) {
        printf("Datos invalidos.\n");
        return EXIT_FAILURE;
    }

    int cajas = objetos / por_caja;
    if (objetos % por_caja != 0) {
        cajas = cajas + 1;
    }
    printf("Cajas necesarias: %d\n", cajas);
    return EXIT_SUCCESS;
}

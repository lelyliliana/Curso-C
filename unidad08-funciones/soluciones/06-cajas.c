#include <stdio.h>

int cajas_necesarias(int objetos, int por_caja)
{
    int cajas = objetos / por_caja;
    if (objetos % por_caja != 0) {
        cajas++;
    }
    return cajas;
}

int main(void)
{
    printf("Cajas para 0: %d\n", cajas_necesarias(0, 5));
    printf("Cajas para 5: %d\n", cajas_necesarias(5, 5));
    printf("Cajas para 17: %d\n", cajas_necesarias(17, 5));
    return 0;
}

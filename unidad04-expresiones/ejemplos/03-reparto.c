#include <stdio.h>

int main(void)
{
    int objetos = 17;
    const int por_caja = 5;
    int cajas_completas = objetos / por_caja;
    int sobrantes = objetos % por_caja;

    printf("Cajas completas: %d\n", cajas_completas);
    printf("Objetos sobrantes: %d\n", sobrantes);
    return 0;
}

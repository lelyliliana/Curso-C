#include <stdio.h>

int main(void)
{
    int cantidad = 12;
    const int *lectura = &cantidad;
    int *const acceso_fijo = &cantidad;
    printf("Lectura inicial: %d\n", *lectura);
    *acceso_fijo = 7;
    printf("Lectura posterior: %d\n", *lectura);
    return 0;
}

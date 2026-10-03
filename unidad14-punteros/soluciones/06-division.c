#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool dividir_con_resto(int objetos, int capacidad, int *cociente, int *resto)
{
    if (cociente == NULL || resto == NULL || cociente == resto) {
        return false;
    }
    if (objetos < 0 || objetos > 100 || capacidad < 1 || capacidad > 100) {
        return false;
    }
    *cociente = objetos / capacidad;
    *resto = objetos % capacidad;
    return true;
}

int main(void)
{
    int cociente = -1;
    int resto = -1;
    if (dividir_con_resto(17, 5, &cociente, &resto)) {
        printf("Cociente: %d; resto: %d\n", cociente, resto);
    }
    if (!dividir_con_resto(17, 0, &cociente, &resto)) {
        printf("Divisor rechazado; conserva %d y %d.\n", cociente, resto);
    }
    return 0;
}

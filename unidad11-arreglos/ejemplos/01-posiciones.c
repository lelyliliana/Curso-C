#include <stdio.h>

int main(void)
{
    int existencias[4] = {12, 7, 0, 9};
    printf("Primero: %d\n", existencias[0]);
    printf("Tercero: %d\n", existencias[2]);
    existencias[1] = 10;
    printf("Segundo actualizado: %d\n", existencias[1]);
    return 0;
}

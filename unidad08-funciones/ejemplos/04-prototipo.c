#include <stdio.h>

int duplicar(int numero);

int main(void)
{
    printf("Doble: %d\n", duplicar(4));
    return 0;
}

int duplicar(int numero)
{
    return numero * 2;
}

#include <stdio.h>

int main(void)
{
    for (int numero = 1; numero <= 10; numero++) {
        if (numero % 2 == 0) {
            continue;
        }
        if (numero > 7) {
            break;
        }
        printf("Impar: %d\n", numero);
    }
    printf("Fin.\n");
    return 0;
}

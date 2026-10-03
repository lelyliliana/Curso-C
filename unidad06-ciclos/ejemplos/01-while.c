#include <stdio.h>

int main(void)
{
    int paso = 1;

    while (paso <= 3) {
        printf("Paso: %d\n", paso);
        paso = paso + 1;
    }
    printf("Fin.\n");
    return 0;
}

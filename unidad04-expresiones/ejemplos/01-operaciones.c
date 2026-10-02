#include <stdio.h>

int main(void)
{
    int a = 7;
    int b = 3;

    printf("Suma: %d\n", a + b);
    printf("Resta: %d\n", a - b);
    printf("Producto: %d\n", a * b);
    printf("Sin parentesis: %d\n", 2 + 3 * 4);
    printf("Con parentesis: %d\n", (2 + 3) * 4);
    return 0;
}

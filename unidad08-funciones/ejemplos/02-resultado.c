#include <stdio.h>

int sumar(int a, int b)
{
    return a + b;
}

int main(void)
{
    int libros = 3;
    int revistas = 4;
    int total = sumar(libros, revistas);

    printf("Total: %d\n", total);
    printf("Otro total: %d\n", sumar(2, 5));
    return 0;
}

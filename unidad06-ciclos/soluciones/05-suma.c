#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int limite = 5;

    if (limite < 0 || limite > 100) {
        printf("Limite invalido.\n");
        return EXIT_FAILURE;
    }
    int suma = 0;
    for (int numero = 1; numero <= limite; numero++) {
        suma += numero;
    }
    printf("Suma: %d\n", suma);
    return EXIT_SUCCESS;
}

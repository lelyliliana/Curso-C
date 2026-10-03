#include <stdio.h>

int main(void)
{
    const int limite = 5;
    int suma = 0;

    for (int numero = 1; numero <= limite; numero++) {
        suma += numero;
    }
    printf("Suma de 1 a %d: %d\n", limite, suma);
    return 0;
}

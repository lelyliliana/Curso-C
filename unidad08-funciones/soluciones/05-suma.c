#include <stdio.h>

int sumar_hasta(int limite)
{
    int suma = 0;
    for (int numero = 1; numero <= limite; numero++) {
        suma += numero;
    }
    return suma;
}

int main(void)
{
    printf("Suma hasta 0: %d\n", sumar_hasta(0));
    printf("Suma hasta 5: %d\n", sumar_hasta(5));
    printf("Suma hasta 100: %d\n", sumar_hasta(100));
    return 0;
}

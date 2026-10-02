#include <stdio.h>

int main(void)
{
    int nota1 = 7;
    int nota2 = 8;
    int nota3 = 8;
    const int cantidad = 3;
    int suma = nota1 + nota2 + nota3;
    double promedio = (double)suma / cantidad;

    printf("Suma: %d\n", suma);
    printf("Promedio: %.2f\n", promedio);
    return 0;
}

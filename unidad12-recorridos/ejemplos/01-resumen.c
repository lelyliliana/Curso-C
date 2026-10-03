#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 5 };

int main(void)
{
    const int lecturas[CAPACIDAD] = {8, 2, 0, 10, 5};
    const size_t usados = 5;
    if (usados > CAPACIDAD) {
        puts("Cantidad invalida.");
        return EXIT_FAILURE;
    }
    if (usados == 0) {
        puts("Sin lecturas: no hay minimo, maximo ni promedio.");
        return EXIT_SUCCESS;
    }
    for (size_t i = 0; i < usados; i++) {
        if (lecturas[i] < 0 || lecturas[i] > 100) {
            puts("Lectura fuera de rango.");
            return EXIT_FAILURE;
        }
    }
    int suma = 0;
    int minimo = lecturas[0];
    int maximo = lecturas[0];
    for (size_t i = 0; i < usados; i++) {
        suma += lecturas[i];
        if (lecturas[i] < minimo) {
            minimo = lecturas[i];
        }
        if (lecturas[i] > maximo) {
            maximo = lecturas[i];
        }
    }
    const double promedio = (double)suma / (double)usados;
    printf("Cantidad: %zu\nSuma: %d\n", usados, suma);
    printf("Minimo: %d\nMaximo: %d\nPromedio: %.2f\n", minimo, maximo, promedio);
    return EXIT_SUCCESS;
}

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum { CAPACIDAD = 7 };

int main(void)
{
    const int visitas[CAPACIDAD] = {3, 0, 5, 2, 0, 4, 1};
    const size_t usados = 7;
    if (usados > CAPACIDAD) {
        puts("Cantidad invalida.");
        return EXIT_FAILURE;
    }
    int total = 0;
    size_t dias_cero = 0;
    size_t mejor = 0;
    for (size_t i = 0; i < usados; i++) {
        if (visitas[i] < 0 || visitas[i] > 100) {
            puts("Visitas fuera de rango.");
            return EXIT_FAILURE;
        }
    }
    for (size_t i = 0; i < usados; i++) {
        total += visitas[i];
        if (visitas[i] == 0) {
            dias_cero++;
        }
        if (visitas[i] > visitas[mejor]) {
            mejor = i;
        }
    }
    printf("Dias: %zu\nTotal: %d\nDias con cero: %zu\n", usados, total, dias_cero);
    if (usados == 0) {
        puts("Sin mejor dia ni promedio.");
    } else {
        printf("Mejor dia: %zu (%d visitas)\n", mejor + 1, visitas[mejor]);
        printf("Promedio: %.2f\n", (double)total / (double)usados);
    }
    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int total = 5;
    int personas = 2;

    if (total < 0 || total > 100 || personas < 1 || personas > 100) {
        printf("Datos invalidos.\n");
        return EXIT_FAILURE;
    }

    double promedio = (double)total / personas;
    printf("Promedio: %.2f\n", promedio);
    return EXIT_SUCCESS;
}

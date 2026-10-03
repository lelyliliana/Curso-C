#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int nota = 7;

    if (nota < 0 || nota > 10) {
        printf("Nota invalida.\n");
        return EXIT_FAILURE;
    }

    if (nota >= 9) {
        printf("Nivel alto.\n");
    } else if (nota >= 6) {
        printf("Aprobado.\n");
    } else {
        printf("Necesita repasar.\n");
    }
    return EXIT_SUCCESS;
}

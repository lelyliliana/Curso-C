#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char grupo = 'B';

    switch (grupo) {
        case 'A':
            printf("Grupo A: manana.\n");
            break;
        case 'B':
            printf("Grupo B: tarde.\n");
            break;
        default:
            printf("Grupo desconocido.\n");
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

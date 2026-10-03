#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Grupo: A, B o C.\n");
    int grupo = getchar();

    if (grupo == EOF) {
        if (ferror(stdin)) {
            printf("Error de lectura.\n");
            return EXIT_FAILURE;
        }
        printf("Fin de entrada.\n");
        return EXIT_SUCCESS;
    }

    bool extra = false;
    if (grupo != '\n') {
        int c = getchar();
        while (c != '\n' && c != EOF) {
            extra = true;
            c = getchar();
        }
        if (ferror(stdin)) {
            printf("Error de lectura.\n");
            return EXIT_FAILURE;
        }
    }

    if (extra || (grupo != 'A' && grupo != 'B' && grupo != 'C')) {
        printf("Entrada invalida.\n");
        return EXIT_FAILURE;
    }
    printf("Grupo aceptado: %c\n", grupo);
    return EXIT_SUCCESS;
}

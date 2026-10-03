#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Opcion: 1 cursos, 2 practica, 0 salir.\n");
    int opcion = getchar();

    if (opcion == EOF) {
        if (ferror(stdin)) {
            printf("Error de lectura.\n");
            return EXIT_FAILURE;
        }
        printf("Fin de entrada.\n");
        return EXIT_SUCCESS;
    }

    bool extra = false;
    if (opcion != '\n') {
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

    if (extra || opcion < '0' || opcion > '2') {
        printf("Entrada invalida.\n");
        return EXIT_FAILURE;
    }
    if (opcion == '1') {
        printf("Ver cursos.\n");
    } else if (opcion == '2') {
        printf("Ver practica.\n");
    } else {
        printf("Salir.\n");
    }
    return EXIT_SUCCESS;
}

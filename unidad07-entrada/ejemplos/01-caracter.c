#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Escribe un digito y pulsa Enter.\n");
    int c = getchar();

    if (c == EOF) {
        if (ferror(stdin)) {
            printf("Error de lectura.\n");
            return EXIT_FAILURE;
        }
        printf("Sin datos.\n");
        return EXIT_SUCCESS;
    }

    if (c >= '0' && c <= '9') {
        printf("Primer digito: %d\n", c - '0');
    } else {
        printf("El primer byte no es un digito.\n");
    }
    return EXIT_SUCCESS;
}

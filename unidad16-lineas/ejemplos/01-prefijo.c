#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const char texto[] = "12abc";
    char *fin = NULL;
    errno = 0;
    const long valor = strtol(texto, &fin, 10);
    if (errno == ERANGE || fin == texto) {
        puts("No se obtuvo un prefijo representable.");
        return EXIT_FAILURE;
    }
    printf("Prefijo convertido: %ld\nResto: %s\n", valor, fin);
    if (*fin != '\0') {
        puts("Conversion parcial: no aceptar como entero completo.");
    }
    return EXIT_SUCCESS;
}

#include <stdio.h>

int main(void)
{
    int libros = 12;
    int copia = libros;

    libros = 9;
    printf("Libros: %d\n", libros);
    printf("Copia: %d\n", copia);

    copia = libros;
    printf("Copia actualizada: %d\n", copia);
    return 0;
}

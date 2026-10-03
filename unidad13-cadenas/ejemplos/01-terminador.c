#include <stddef.h>
#include <stdio.h>

int main(void)
{
    char inicial = 'C';
    char curso[] = "C";
    char vacia[] = "";
    printf("Inicial: %c\nCurso: %s\n", inicial, curso);
    printf("Capacidad de curso: %zu\n", sizeof curso);
    printf("Capacidad de vacia: %zu\n", sizeof vacia);
    if (curso[1] == '\0') {
        puts("El terminador esta en el indice 1.");
    }
    return 0;
}

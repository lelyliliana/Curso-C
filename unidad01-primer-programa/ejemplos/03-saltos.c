#include <stdio.h>

int main(void)
{
    /* Sin salto, la siguiente llamada sigue en la misma linea. */
    printf("Uno");
    printf("Dos\n");
    /* Dos saltos dejan una linea vacia. */
    printf("Tres\n\n");
    printf("Fin\n");
    return 0;
}

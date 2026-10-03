#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int tabla = 7;

    if (tabla < 1 || tabla > 10) {
        printf("Tabla invalida.\n");
        return EXIT_FAILURE;
    }
    for (int factor = 1; factor <= 10; factor++) {
        printf("%d x %d = %d\n", tabla, factor, tabla * factor);
    }
    return EXIT_SUCCESS;
}

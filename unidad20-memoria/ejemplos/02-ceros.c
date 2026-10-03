#include <stdio.h>
#include <stdlib.h>
int main(void) {
    size_t cantidad = 3;
    int *datos = calloc(cantidad, sizeof *datos);
    if (datos == NULL) { fputs("Sin memoria.\n", stderr); return EXIT_FAILURE; }
    for (size_t i = 0; i < cantidad; ++i) printf("%d\n", datos[i]);
    free(datos);
    return EXIT_SUCCESS;
}

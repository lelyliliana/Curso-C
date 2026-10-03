#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const int max_intentos = 3;
    int intentos = 0;
    bool aceptada = false;
    bool terminado = false;

    while (intentos < max_intentos && !aceptada && !terminado) {
        printf("Opcion: 1 cursos, 2 practica, 0 salir.\n");
        int opcion = getchar();

        if (opcion == EOF) {
            if (ferror(stdin)) {
                printf("Error de lectura.\n");
                return EXIT_FAILURE;
            }
            printf("Fin de entrada.\n");
            terminado = true;
        } else {
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

            intentos++;
            if (!extra && opcion >= '0' && opcion <= '2') {
                aceptada = true;
                printf("Opcion aceptada: %c\n", opcion);
            } else {
                printf("Entrada invalida.\n");
            }
        }
    }

    if (!aceptada && !terminado) {
        printf("Limite de intentos alcanzado.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

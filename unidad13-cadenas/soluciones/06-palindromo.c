#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAXIMO = 12, CAPACIDAD = MAXIMO + 1 };

bool simbolo_permitido(int byte)
{
    const char permitidos[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-";
    for (size_t i = 0; i < sizeof permitidos - 1; i++) {
        if (byte == permitidos[i]) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    char etiqueta[CAPACIDAD] = {0};
    size_t usados = 0;
    bool hubo_datos = false;
    bool invalida = false;
    int byte;
    puts("Etiqueta de 1 a 12: letras inglesas, digitos, _ o -.");
    while ((byte = getchar()) != '\n' && byte != EOF) {
        hubo_datos = true;
        if (!simbolo_permitido(byte)) {
            invalida = true;
        } else if (usados >= CAPACIDAD - 1) {
            invalida = true;
        } else if (!invalida) {
            etiqueta[usados] = (char)byte;
            usados++;
        }
    }
    if (byte == EOF && ferror(stdin)) {
        puts("Error de lectura.");
        return EXIT_FAILURE;
    }
    if (byte == EOF && !hubo_datos) {
        puts("Fin sin etiqueta.");
        return EXIT_SUCCESS;
    }
    if (invalida || usados == 0) {
        puts("Etiqueta invalida.");
        return EXIT_FAILURE;
    }
    etiqueta[usados] = '\0';
    bool palindromo = true;
    for (size_t i = 0; i < usados / 2; i++) {
        if (etiqueta[i] != etiqueta[usados - 1 - i]) {
            palindromo = false;
            break;
        }
    }
    printf("Etiqueta: %s\n", etiqueta);
    if (palindromo) {
        puts("Palindromo: si.");
    } else {
        puts("Palindromo: no.");
    }
    return EXIT_SUCCESS;
}

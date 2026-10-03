#ifndef CURSO_C_ENTRADA_H
#define CURSO_C_ENTRADA_H

enum ResultadoLectura {
    LECTURA_INVALIDA = -1,
    LECTURA_FIN = -2,
    LECTURA_ERROR = -3
};

/* Devuelve 0..100 o un estado LECTURA_*; consume una linea. */
int leer_cantidad(void);

#endif

#include "estado.h"
#include <stddef.h>
const char *nombre_estado(enum Estado estado)
{
    switch (estado) {
    case APAGADO: return "APAGADO";
    case LISTO: return "LISTO";
    case ACTIVO: return "ACTIVO";
    case FALLO: return "FALLO";
    default: return "DESCONOCIDO";
    }
}
bool transicionar(enum Estado *estado, enum Evento evento)
{
    if (estado == NULL) {return false;}
    if (*estado != APAGADO && *estado != LISTO && *estado != ACTIVO && *estado != FALLO) {
        return false;
    }
    enum Estado siguiente = *estado;
    if (evento == ERROR_DETECTADO) {
        siguiente = FALLO;
    } else if (*estado == APAGADO && evento == ENCENDER) {
        siguiente = LISTO;
    } else if (*estado == LISTO && evento == INICIAR) {
        siguiente = ACTIVO;
    } else if (*estado == ACTIVO && evento == DETENER) {
        siguiente = LISTO;
    } else if (*estado == FALLO && evento == RESTABLECER) {
        siguiente = APAGADO;
    } else {
        return false;
    }
    *estado = siguiente;
    return true;
}

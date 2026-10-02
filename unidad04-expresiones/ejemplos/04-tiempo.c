#include <stdio.h>

int main(void)
{
    int minutos_totales = 135;
    const int minutos_por_hora = 60;
    int horas = minutos_totales / minutos_por_hora;
    int minutos_restantes = minutos_totales % minutos_por_hora;
    int segundos_totales = minutos_totales * 60;

    printf("Horas: %d\n", horas);
    printf("Minutos restantes: %d\n", minutos_restantes);
    printf("Segundos totales: %d\n", segundos_totales);
    return 0;
}

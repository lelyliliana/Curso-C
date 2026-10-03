# Unidad 13 — Ejercicios

[Guía](README.md) · [Soluciones](SOLUCIONES.md)

Antes de construir cada programa, escribe capacidad, longitud válida y posición del terminador. No ejecutes ejemplos con cadenas sin terminar.

## 1. Texto y terminador

Dibuja una tabla de índices para `char palabra[] = "sol";` y para `char vacia[] = "";`. ¿Cuánto ocupa cada arreglo? ¿Cuál es su longitud? Explica por qué `char letras[3] = {'s', 'o', 'l'};` no puede imprimirse directamente con `%s`.

## 2. Longitud y capacidad

Predice `ejemplos/02-longitud.c`. Cambia el inicializador de `nombre[12]` a `"Ana"` y luego a `""`. Conserva la asignación `nombre[0] = 'M'` del ejemplo. ¿Qué texto y longitud hay antes del cambio? ¿Qué se imprime después? La inicialización completa del arreglo deja ceros en las posiciones restantes: utiliza esa información en tu explicación.

## 3. Comparar dos textos

En `ejemplos/03-comparacion.c`, explica el cero de `strcmp` y por qué no utilizamos `==` para comparar el contenido. Compara luego `"sensor"` con `"sensor_2"`: son distintos aunque tengan un prefijo compartido. No exijas que un resultado no nulo sea exactamente 1 o -1.

## 4. Copia con capacidad seis

Crea una copia de `"Leli"` a un destino de seis `char`. Calcula la longitud de ese origen válido, comprueba espacio, copia con un ciclo y escribe el terminador. Espera `Copia: Leli` y `Longitud: 4`.

Prueba después con `"abcde"`, `"abcdef"` y `""`: el primero cabe, el segundo se rechaza con `Texto demasiado largo.`, y el vacío produce una copia válida de longitud cero. La copia admite vacío; la política del lector de etiquetas no lo admite. No son el mismo contrato.

## 5. Contar dígitos de una etiqueta

Parte de `ejemplos/04-etiqueta.c`. Conserva todo el contrato de lectura y agrega un recorrido de los símbolos almacenados **después** de validar y terminar la cadena. Cuenta los que están entre `'0'` y `'9'`.

Con `sensor_2` espera 1; con `A12-3` espera 3; con `abc` espera 0. Con una línea vacía, un espacio, un byte nulo o trece símbolos no se presenta un conteo parcial. Una entrada válida de doce dígitos debe producir 12.

## 6. Palíndromo exacto

Reutiliza el mismo lector. Una etiqueta es palíndroma si se lee igual desde ambos extremos. Compara parejas de índices, como en la inversión de la Unidad 12, sin modificar el texto. Detén la comparación al encontrar una diferencia.

| Etiqueta | Resultado |
|---|---|
| `radar` | Sí |
| `abba` | Sí |
| `A` | Sí |
| `A-a` | No |
| `sensor_2` | No |
| `12-21` | Sí |

La comparación distingue mayúsculas y minúsculas; conserva guiones, dígitos y guiones bajos. No elimina símbolos ni implementa equivalencia de letras con tilde. Las entradas que incumplen el contrato del lector se rechazan antes de comparar.

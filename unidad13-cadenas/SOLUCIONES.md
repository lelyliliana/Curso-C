# Unidad 13 — Soluciones razonadas

[Guía](README.md) · [Ejercicios](EJERCICIOS.md)

## 1. Terminador

| Arreglo | Índices y contenido | Capacidad | Longitud |
|---|---|---:|---:|
| `palabra` | 0: `'s'`, 1: `'o'`, 2: `'l'`, 3: `'\0'` | 4 | 3 |
| `vacia` | 0: `'\0'` | 1 | 0 |

`letras[3]` contiene solo tres letras. `%s` seguiría buscando un terminador más allá del objeto y no tiene un límite recibido que lo proteja. No lo ejecutamos como cadena. Un arreglo de cuatro elementos inicializado con `"sol"` sí proporciona ese terminador.

## 2. Cambiar longitud

La capacidad permanece en doce; la longitud inicial cambia con el texto. Con `"Ana"` se imprimen tres letras y luego `Mna`. Con `""` la longitud inicial es cero y el ciclo de impresión de letras no entra. Al cambiar `nombre[0]` a `'M'`, el índice 1 sigue en cero por la inicialización: después se imprime `M`. Ya no es una cadena vacía, aunque la variable `longitud` siga guardando el resultado anterior, cero.

Ese resultado muestra otra distinción: almacenar una longitud calculada no la actualiza automáticamente al modificar el texto. Si necesitas la longitud posterior, vuelve a calcularla cuando la cadena siga siendo válida.

## 3. Comparación

Cero significa igualdad de contenido entre dos cadenas terminadas. Entre `"sensor"` y `"sensor_2"` hay diferencia: el terminador del primer texto aparece donde el segundo aún tiene `_`. Un prefijo compartido no basta. `==` entre nombres de arreglos no recorre letras; no mide igualdad de texto.

## 4. Copia

Fuente completo: [soluciones/04-copia.c](soluciones/04-copia.c). Salida inicial:

```text
Copia: Leli
Longitud: 4
```

La longitud cuatro es menor que capacidad seis: quedan espacio para el terminador y una posición sin utilizar. La variante de cinco letras usa índices 0–4 y termina en 5. La de seis se rechaza antes de copiar, porque necesitaría siete elementos.

Con origen vacío, el ciclo no entra y se escribe el terminador en 0. La salida es `Copia: ` seguida de salto y `Longitud: 0`. La validez de una cadena vacía en C es independiente de si una aplicación decide aceptarla.

## 5. Dígitos

Fuente: [soluciones/05-digitos.c](soluciones/05-digitos.c). Con `sensor_2`:

```text
Etiqueta de 1 a 12: letras inglesas, digitos, _ o -.
Etiqueta: sensor_2
Digitos: 1
```

La lectura se conserva y el conteo solo ocurre en su rama válida. C garantiza que los caracteres básicos `'0'` hasta `'9'` tienen códigos consecutivos; por eso este intervalo identifica dígitos de la lista. No generalizamos ese supuesto a todas las letras de cualquier codificación.

El contador es independiente de `usados`: con `abc`, usados es tres y dígitos cero. Con doce dígitos ambos valen doce. No hay un dígito adicional por el terminador.

## 6. Palíndromo

Fuente: [soluciones/06-palindromo.c](soluciones/06-palindromo.c). Con `radar`:

```text
Etiqueta de 1 a 12: letras inglesas, digitos, _ o -.
Etiqueta: radar
Palindromo: si.
```

El algoritmo empieza suponiendo igualdad y busca una pareja que la contradiga. Con cinco símbolos compara 0/4 y 1/3; el centro coincide consigo mismo y no necesita comparación. Con uno, no hay parejas diferentes y el resultado es sí. La resta del índice opuesto solo se calcula cuando la condición del ciclo permite hacerlo.

`A-a` no coincide porque `'A'` difiere de `'a'`. `12-21` sí coincide. El texto no se modifica ni se normaliza: se aplica la definición exacta del ejercicio.

## Por qué se repite el lector en estos dos programas

Los fuentes de soluciones son programas completos y pueden compilarse de forma independiente. Conservan la misma lógica de lectura para practicar el procesamiento posterior. La función `simbolo_permitido` ya separa un cálculo que recibe un entero por valor.

Extraer la lectura a una función que llene un arreglo del llamador requiere comprender acceso mediante punteros y capacidad explícita. Ese será el siguiente bloque. Esta repetición temporal no es una recomendación de mantener varios lectores divergentes en una aplicación real; al crear la interfaz compartida, las pruebas deberán verificar la misma implementación.

## Evidencia de cierre

Conserva código, comandos y resultados para longitudes 1, 12 y 13, una línea vacía y fin sin datos. Explica por qué el programa no imprime una etiqueta aceptada si un símbolo inválido aparece después de un prefijo válido.

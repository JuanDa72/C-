# 👨‍👧‍👦 Apuntes: Creación de Procesos con `fork()` en C

## 🎯 Objetivo de la función `fork()`

La función `fork()` (llamada al sistema) se utiliza en sistemas operativos tipo Unix (como Linux) para crear un **nuevo proceso** a partir de uno existente.

### Concepto Clave: Duplicación de Procesos

El objetivo principal es la **duplicación** del proceso.

* El proceso original se denomina **Proceso Padre**.
* La copia recién creada se denomina **Proceso Hijo**.

El proceso hijo es una copia casi exacta del padre, heredando:
* Una copia de la **memoria** del padre.
* Una copia de los **descriptores de archivo** abiertos.
* El **contador de programa**, por lo que ambos procesos continúan su ejecución inmediatamente después de la línea donde se llamó a `fork()`.



---

## 💻 Guía Paso a Paso para Usar `fork()` en C

Para que el proceso Padre y el proceso Hijo realicen tareas diferentes (que es el uso más común), debes inspeccionar el valor que retorna la función `fork()`.

### Paso 1: Incluir las Librerías Necesarias

Necesitarás las siguientes cabeceras:

* **`<unistd.h>`**: Contiene la declaración de `fork()`, `getpid()` y `getppid()`.
* **`<sys/types.h>`**: Define el tipo de dato `pid_t` (tipo para identificadores de proceso).
* **`<stdio.h>`**: Para funciones de entrada/salida como `printf()` y `perror()`.
* **`<stdlib.h>`**: Para `exit()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // Recomendado para que el padre espere al hijo



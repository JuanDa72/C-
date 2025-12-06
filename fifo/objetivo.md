# 📤 Apuntes: Comunicación entre Procesos No Emparentados (FIFOs)

## 🎯 Objetivo del Proceso: Comunicación Asíncrona

El objetivo principal de este proceso (usando `escritor.c` y `lector.c`) es establecer un canal de comunicación **unidireccional** entre dos procesos que **no tienen relación de parentesco** (es decir, no fueron creados por el mismo `fork()`).

### 🔑 Mecanismo Clave: FIFO (Pipe Nombrado)

Mientras que los pipes normales (`pipe()`) solo funcionan entre un padre y sus hijos porque estos heredan los descriptores de archivo, un **FIFO (First-In, First-Out)**, también conocido como **pipe nombrado**, permite la comunicación entre cualquier par de procesos.

* **¿Cómo funciona?** El FIFO crea un **archivo especial** en el sistema de archivos (en este caso, `/tmp/mi_fifo_test`). Este "archivo" no contiene datos persistentes como un archivo normal, sino que actúa como un **punto de encuentro** en el sistema operativo.

### 📝 Flujo de la Comunicación

| Rol del Proceso | Función Principal | Llamada Clave |
| :--- | :--- | :--- |
| **Escritor (`escritor.c`)** | Inicia el canal y envía los datos. | `mkfifo()` y `open(..., O_WRONLY)` |
| **Lector (`lector.c`)** | Espera en el canal y recibe los datos. | `open(..., O_RDONLY)` y `read()` |



---

## 🚦 Bloqueo y Sincronización

Un objetivo crucial de los FIFOs es la **sincronización implícita** de los procesos:

1.  **Apertura Bloqueante:** Por defecto, cuando un proceso intenta abrir un FIFO, se **bloquea** (pausa) hasta que el otro proceso abre el extremo opuesto.
    * Si el **Lector** se ejecuta primero, se bloquea en `open(..., O_RDONLY)` hasta que el **Escritor** abre el lado `O_WRONLY`.
    * Esto asegura que el canal esté listo en ambos extremos antes de que se intente cualquier transferencia de datos.

2.  **Transferencia de Datos:** Una vez abierto, el Escritor puede usar **`write()`** para depositar datos, y el Lector usa **`read()`** para extraerlos. Los datos son tratados como un *stream* de bytes.

3.  **Finalización:** Cuando el Escritor cierra su descriptor (`close(fd)`), el Lector recibe un **fin de archivo (EOF)** en su siguiente intento de `read()`, lo que le indica que la comunicación ha terminado y que puede continuar su ejecución.

4. Es probable que se tengan dos archivos los cuales establecen la comunicación entre si, por lo tanto es necesario compilar los archivos, ejecutar primero el lector y luego el escritor, para que pasen los datos :D

## Es comun que para eliminar el archivo intermedio que creamos utilciemos:
rm /tmp/mi_fifo_test
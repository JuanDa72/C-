# 🧠 Memoria Compartida (Shared Memory) - System V

## 📖 Concepto General

La **Memoria Compartida** es el mecanismo de Comunicación Inter-Procesos (IPC) **más rápido** que existe en sistemas Unix/Linux.

### ¿Cómo funciona?
El Sistema Operativo reserva un bloque de memoria física (RAM) y permite que múltiples procesos mapeen ese mismo bloque en su propio espacio de direcciones virtuales.
1. **Sin copias:** A diferencia de los *Pipes* o *Sockets*, los datos no viajan de un lado a otro; los datos "están ahí" para todos al mismo tiempo.
2. **Acceso directo:** Los procesos leen y escriben como si fuera una variable local o un *array* propio.

### ⚠️ El Gran Reto: Sincronización
Al ser tan rápida y directa, el SO **no interviene** en cada lectura/escritura.
* **Problema:** Si dos procesos escriben a la vez, ocurre una **Condición de Carrera** (*Race Condition*) y los datos se corrompen.
* **Solución:** Es obligatorio usar mecanismos de sincronización externos como **Semáforos** o **Mutex** para coordinar quién entra a la memoria.

---

## 📚 Librerías Necesarias

Para utilizar la API de System V en C:

```c
#include <sys/ipc.h>   // Constantes de IPC (IPC_CREAT, etc.)
#include <sys/shm.h>   // Funciones shmget, shmat, shmdt, shmctl
#include <sys/types.h> // Definiciones de tipos (key_t, pid_t)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // Para memcpy o strcpy
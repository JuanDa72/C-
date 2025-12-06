## 🟦 ¿Qué es un semáforo POSIX?

Es una herramienta que te permite sincronizar procesos o hilos, igual que un semáforo System V, pero con una API más directa:

Se usa con funciones como:

    sem_open() → crear/abrir un semáforo

    sem_wait() → esperar (down)

    sem_post() → liberar (up)

    sem_close() → cerrar

    sem_unlink() → eliminar

🟩 Tipos de semáforos POSIX
✔ Semáforos con nombre

Pueden ser compartidos entre procesos diferentes.

sem_t *sem = sem_open("/mi_semaforo", O_CREAT, 0666, 0);

✔ Semáforos sin nombre

Se usan entre hilos o procesos con memoria compartida y requieren que el semáforo esté en memoria compartida.

sem_t sem;
sem_init(&sem, 1, 0);   // 1 = compartido entre procesos

🟦 ¿Por qué son mejores que System V?
POSIX	System V
API simple	API larga y vieja
semáforos con nombre	semáforos con ID numérico
no necesitas ftok()	necesitas claves e IPC antiguos
menos código	más verboso

| Operación       | POSIX          |
| --------------- | -------------- |
| Crear semáforo  | `sem_open()`   |
| Esperar (down)  | `sem_wait()`   |
| Liberar (up)    | `sem_post()`   |
| Cerrar semáforo | `sem_close()`  |
| Borrarlo        | `sem_unlink()` |

## importante
Ten en cuenta que los semaforos tiene un valor asociado, al crearlos podemos indicar cual es el valor en su creación, 0 indica que esta protegido y ningun proceso mas puede entrar 
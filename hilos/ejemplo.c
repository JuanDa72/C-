#include <stdio.h>
#include <pthread.h>

#define N 100000

int contador = 0;            // Recurso compartido
pthread_mutex_t lock;        // Declaración del mutex

void *sumar(void *arg) {
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&lock);   // Bloquea acceso
        contador++;
        pthread_mutex_unlock(&lock); // Libera acceso
    }
    return NULL;
}

int main() {
    pthread_t hilo1, hilo2;

    // Inicializar mutex
    pthread_mutex_init(&lock, NULL);

    // Crear hilos
    pthread_create(&hilo1, NULL, sumar, NULL);
    pthread_create(&hilo2, NULL, sumar, NULL);

    // Esperar a que terminen
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Destruir el mutex
    pthread_mutex_destroy(&lock);

    printf("Valor final del contador: %d\n", contador);

    return 0;
}

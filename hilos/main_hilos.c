#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ITERATIONS 100000000

void load_l(){
    double x = 0;
    for (int i = 0; i < ITERATIONS; i++){
        x = x + sin(i) * cos(i);
    }
}

void *function_thread(void *id){
    int thread_id = *((int *)id);
    printf("Hilo %d iniciado\n", thread_id);
    load_l();
    printf("Hilo %d terminado\n", thread_id);
    return (void *)(long)1;  // Cast seguro
}

int main(){
    pthread_t hilo1, hilo2;
    int id1 = 1, id2 = 2;
    void *retval1, *retval2;
    
    // Crear primer hilo (sin cast innecesario)
    int r1 = pthread_create(&hilo1, NULL, function_thread, (void *)&id1);
    if(r1 != 0){
        perror("Error en pthread_create");
        return 1;
    }

    // Crear segundo hilo (sin cast innecesario)  
    int r2 = pthread_create(&hilo2, NULL, function_thread, (void *)&id2);
    if(r2 != 0){
        perror("Error en pthread_create");
        return 1;
    }

    // Esperar hilos
    pthread_join(hilo1, &retval1);
    pthread_join(hilo2, &retval2);

    // Verificar con cast correcto
    if((long)retval1 != 1){
        printf("Advertencia: Hilo 1 retornó valor inesperado: %ld\n", (long)retval1);
    }
    if((long)retval2 != 1){
        printf("Advertencia: Hilo 2 retornó valor inesperado: %ld\n", (long)retval2);
    }

    printf("Todos los hilos terminaron!\n");
    return 0;
}



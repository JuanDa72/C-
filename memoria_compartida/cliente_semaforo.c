#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#define TAM 1024

int main (){

     // Conectar memoria compartida
    key_t clave = ftok("memoria_2", 'A');
    int shmid = shmget(clave, TAM, 0666);
    char *data = shmat(shmid, NULL, 0);

    sem_t *sem = sem_open("/mi_semaforo", 0);

    printf("Cliente esperando...\n");

    sem_wait(sem);
    printf("Mensaje recibido: %s\n", data);

    //smhdt se usa para desconectar la memoria compartida
    shmdt(data);

    //Cerrar el semaforo
    sem_close(sem);
    sem_unlink("/mi_semaforo");

    return 0;
}
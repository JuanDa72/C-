#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h> // Para O_CREAT, O_EXCL

#define TAM 1024

int main(){

    key_t clave = ftok("memoria_2", 'A');
    int shmid = shmget(clave, TAM, IPC_CREAT | 0666);
    char *data = shmat(shmid, NULL, 0);

    sem_t *sem = sem_open("/mi_semaforo", O_CREAT, 0666, 0);

    printf("Servidor escribiendo...\n");
    strcpy(data, "Hola desde POSIX!");

    // Señalizar al cliente que puede leer
    sem_post(sem);

    shmdt(data);

    sem_close(sem);

    return 0;
}
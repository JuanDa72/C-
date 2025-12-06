#include <stdio.h>
#include <sys/ipc.h> //sirve para ftok
#include <sys/shm.h> //sirve para shmget, shmat, shmd
#include <stdlib.h> //sirve para exit
#include <string.h> //sirve para memset

#define tam 1024

int main(){
    key_t key=ftok("memoria",65); //Genera una clave unica para la memoria compartida

    int shmId=shmget(key, tam, 0666|IPC_CREAT); //Crea el segmento de memoria compartida
    if(shmId<0){
        perror("Error en shmget");
        exit(1);
    }

    char *data=(char *)shmat(shmId,NULL,0); //Se adjunta el segmento de memoria compartida al espacio de direcciones del proceso
    if(data==(char *)-1){
        perror("Error en shmat");
        exit(1);
    }

    sprintf(data,"Hola desde el servidor de memoria compartida");
    printf("Mensaje escrito en memoria compartida: %s\n",data);

    shmdt(data); //Se desadjunta el segmento de memoria compartida del espacio de direcciones del proceso

    return 0;



}
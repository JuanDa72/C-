#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/shm.h>

#define TAM 1024

int main(){
    key_t key=ftok("memoria",65); //Genera una clave unica para la memoria compartida

    int shmId=shmget(key, TAM, 0666); //Obtiene el segmento de memoria compartida
    if(shmId<0){
        perror("Error en shmget");
        exit(1);
    }

    char *data=(char *)shmat(shmId,NULL,0); //Se adjunta el segmento de memoria compartida al espacio de direcciones del proceso
    if(data==(char *)-1){
        perror("Error en shmat");
        exit(1);
    }

    printf("Mensaje recibido de memoria compartida: %s\n",data);

    shmdt(data); //Se desadjunta el segmento de memoria compartida del espacio de direcciones del proceso

    return 0;
}



//Para que funcione hay que crear el archivo memoria 



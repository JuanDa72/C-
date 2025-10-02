#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>


int main(){

    key_t key=12345;

    double *ap;

    int status;

    int shmId=shmget(key, sizeof(double), IPC_CREAT | 0666);

    if(shmId<0){
        perror("Error en shmget");
        exit(1);
    }

    ap=(double *)shmat(shmId, NULL, 0);
    //Null indica que el so asigne cualquier direccioń mientras que 0 que sea 
    // de lectura y escritura

    int pid=fork();

    if(pid<0){
        perror("Error en fork");
        exit(1);
    }   

    if(pid==0){
        *ap=3.1415926525;
    }

    else{
        wait(&status);
        printf("Valor de pi: %lf\n", *ap);

        shmdt(ap);
        shmctl(shmId, IPC_RMID, NULL);
        return 0;
    }

}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>



int esPrimo(int number){
    int value=1;
    for(int i=2; i<number; i++){
        if(number%i==0){
            value=0;
            break;
        }
    }
    return value;
}


int main(){

    //clave
    key_t key=12345;

    double *ap;
    int shm_id;
    int count;
    pid_t pid;
    int *first_value;
    int status;

    shm_id=shmget(key, sizeof(int), IPC_CREAT|0666);

    if(shm_id<0){
        perror("Error al crear smhget");
    }

    //Adjuntar la sección de memoria al proceso
    ap=shmat(shm_id, NULL, 0);

    //Parte del menu
    int start;
    int finish;


    printf("Ingrese el número de inicio del intervalo: ");
    scanf("%d",&start);

    printf("Ingrese el número del final del intervalo: ");
    scanf("%d",&finish);

    //Creación del hijo
    pid=fork();

    int range=finish-start;
    int mid;
    if(range%2==0){
        mid=range/2;
    }

    else{
        mid=(range/2)+1;
    }

    if(pid<0){
        perror("Error al crear el proceso hijo");
    }

    else if(pid==0){
        int count=0;
        for(int i=start; i<=mid+start; i++){
            int result=esPrimo(i);
            count+=result;
            if(result==1){
                printf("%d\n",i);
            }
        }

        *ap=count;
    }


    //Parte del padre
    else{
        wait(&status);
        int st=mid+1;
        count=0;
        for(int i=st; i<=finish; i++){
            int result=esPrimo(i);
            count+=result;
            if(result==1){
                printf("%d\n",i);
            }
        }

        
        int fr=count + *ap;

        printf("El numero de primos que hay en este intervalo son: %d", fr);
        shmdt(ap);
        shmctl(shm_id, IPC_RMID, NULL);
        return 0;
    }
}
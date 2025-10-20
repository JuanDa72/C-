#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>



#define MAX_PROCESOS 1
#define NUM_HILOS 11
pthread_mutex_t lock;

struct datos_tipo{
    int dato;
    int p;
};


void *proceso(void *datos){
    struct datos_tipo *datos_proceso;
    datos_proceso = (struct datos_tipo *)datos;
    int a,i,p;

    a=datos_proceso -> dato;
    p=datos_proceso -> p;

    //--->


    pthread_mutex_lock(&lock);

    for(int i=0; i<p; i++){
        printf("%i", a);
    }   

    ///Indica al programa que no espera a que se llene el buffer si no que envíe todo de inmediato
    fflush(stdout); 
    
    sleep(1);
    for(i=0; i<p; i++){
        printf("- ");
    }

    fflush(stdout);


    // --->
    pthread_mutex_unlock(&lock);
    return NULL;


}


int main(){

    int i;
    char* valor_devuelto;
    
    /*Variables para hilos*/
    struct datos_tipo datos_hilo[NUM_HILOS];
    pthread_t idhilo[NUM_HILOS];

    pthread_mutex_init(&lock, NULL);


    for(i=0; i<NUM_HILOS; i++){
        datos_hilo[i].dato=i;
        datos_hilo[i].p=i+1;
    }
    
    for (i=0; i<NUM_HILOS; i++){
        if(pthread_create(&idhilo[i], NULL, proceso, (void *)&datos_hilo[i])!=0){
            perror("No se ha podido crear el hilo");
            exit(-1);
        }
    }


    for(i=0; i<NUM_HILOS; i++){
        if(pthread_join(idhilo[i], (void **)&valor_devuelto)!=0){
            perror("No se ha podido esperar al hilo");
            exit(-1);
        }
    }

    pthread_mutex_destroy(&lock);  

    return 0;


}


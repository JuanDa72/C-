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
        }
    }
    return value;
}



int main(){


    //Parte del menu
    int start;
    int finish;


    printf("Ingrese el número de inicio del intervalo: ");
    scanf("%d",&start);

    printf("Ingrese el número del final del intervalo: ");
    scanf("%d",&finish);

    printf("El inicio es %d\n", start);
    printf("El final es %d\n", finish);

    //Veriificacion de que obtiene la mitad xd
    int mid;
    int range=finish-start;
    if(range%2==0){
        mid=range/2;
    }

    else{
        mid=(range/2)+1;
    }

    printf("La mitad para este caso es %d\n", mid);
    printf("Va a evaluar hasta %d\n", mid+start);

    int count=0;
        for(int i=start; i<=mid+start; i++){
            int result=esPrimo(i);
            count+=result;
        }

    printf("La cantidad de primos en la primera parte es %d",count);

}
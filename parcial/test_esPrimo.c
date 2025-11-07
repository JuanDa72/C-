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

    

}
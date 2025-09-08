#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    srand(time(NULL)); //Semilla para numeros aleatorios
    printf("%d", rand()); //Numero aleatorio

}
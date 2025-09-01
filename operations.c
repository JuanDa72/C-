#include <stdio.h>
#include <stdbool.h>

//Repasando un poco las opeeraciones basicas en c
//Recuerda que si manejams enteros, en una división el resultado sera truncado

int main(){

    int x=4;
    int y=9;
    int z;

    z=y/x;
    printf("%d \n",z); //Imprime 2

    //Si quisieramos la parte decimal tendríamos que definir al menos 
    //el denominador como flotante y el resultado tambien

    float q=4;
    float w;
    w=y/q;
    printf("%f \n",w);


    return 0;

}

#include <stdio.h> //Entrada y salida
#include <stdlib.h> //Funciones de utilidad general
#include <unistd.h> //Llamadas al sistema: fork, exec, etc.
#include <sys/types.h> //Tipos de datos útil para el pid
#include <sys/wait.h> //Para esperar a los procesos hijos

#define BUFFER_SIZE 100 //Para definir el tamaño del buffer, podría
//tambien un numero o algo asi y se usa sizeof

int main(){
    //fd[0] para leer, fd[1] para escribir
    int fd[2]; //Definir el arreglo para el pipe

    pid_t pid;

    char mensajePadre[] = "Hola desde el proceso padre";
    char buffer_hijo[BUFFER_SIZE];


    //creacion del pipe
    if(pipe(fd) == -1){
        perror("Error al crear el pipe");
        return -1;
    }

    //Hacer el fork 
    pid = fork();

    if(pid < 0){
        perror("Error al crear el proceso hijo");
        return -1;
    }

    //Definimos el comportamiento del padre xd
    if(pid!=0){
        close(fd[0]); //Cerramos el extremo de lectura
        if(write(fd[1], mensajePadre, sizeof(mensajePadre))==-1){
            perror("Error al escribir en el pipe");
            return -1;
        }

        //cerramos escritura
        close(fd[1]);
        wait(NULL); //Esperar al hijo
    }

    else {
        close(fd[1]); //Cerramos el extremo de escritura
        if(read(fd[0], buffer_hijo, sizeof(mensajePadre))==-1){
            perror("Error al leer del pipe");
            return -1;
        }       

        printf("Mensaje recibido del padre: %s\n", buffer_hijo);
        close(fd[0]); //Cerramos el extremo de lectura
    }

    return 0;

}
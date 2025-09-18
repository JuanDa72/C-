#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    int pipe_fd[2];
    char buffer[5];

    int r=pipe(pipe_fd);
    if(r<0){
        perror("error al crear pipe");
        exit(1);
    }

    //proceso hijo
    pid_t pid=fork();
    if(pid<0){
        perror("error al crear proceso hijo");
        exit(1);
    } 
    
    if(pid==0){
        close(pipe_fd[0]); //cerrar lectura 
        r=write(pipe_fd[1], "hola", 5);
        close(pipe_fd[1]); //cerrar escritura
        exit(0);
    }
    
    else{
        close(pipe_fd[1]); //cerrar escritura
        r=read(pipe_fd[0], buffer, 5);
        printf("mensaje recibido: %s\n", buffer);


        close(pipe_fd[0]); //cerrar lectura
        wait(NULL); //esperar a que termine el hijo
        exit(0);
    }


}
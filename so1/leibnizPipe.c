#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    int pipe_fd[2];
    
    //Creo que no definiremos un buffer explicitamente 
    int r=pipe(pipe_fd);
    if(r<0){
        perror("error al crear pipe");
        exit(1);   
    }

    //Variables en común que usarán ambos procesos
    int cantidad = 500000000;
    double acc = 0;
    double opened;

    //Uso de fork 
    pid_t pid=fork();
    if(pid<0){
        perror("error al crear proceso hijo");
        exit(1);
    }

    else if(pid==0){ //Proceso hijo
        close(pipe_fd[0]); //cerrar lectura 

        for (int i = 1; i < cantidad; i++){
            acc -= 4.0/(4.0*i - 1.0);     
        }
        printf("negativos: %.10f\n", acc);
        
        //Escribo en el pipe
        r=write(pipe_fd[1], &acc, sizeof(acc));
        close(pipe_fd[1]); //cerrar escritura
        exit(0);
    }
    
    else{ //Proceso padre
        close(pipe_fd[1]); //cerrar escritura

        for (int i = 0; i < cantidad; i++){
            acc += 4.0/(4.0*i + 1.0);  
        }
        printf("positivos: %.10f\n", acc);

        //Leo del pipe
        r=read(pipe_fd[0], &opened, sizeof(double));
        acc += opened;
        printf("pi: %.10f\n", acc);

        close(pipe_fd[0]); //cerrar lectura
        wait(NULL); //esperar a que termine el hijo
        exit(0);
    }

}
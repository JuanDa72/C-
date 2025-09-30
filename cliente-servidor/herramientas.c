#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>

static int global_socket_fd=-1;

int reuse(int socket_fd){
    int status=1;  

    if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &status, sizeof(status))<0){
        perror("Error al intentar reiniciar el puerto");
        return -1;
    }

    return 0;

}

void manejar_control_c(int sigmal){
    printf("\n Inicio de función manejar_control_c. \n");

    if(global_socket_fd != -1){
        close(global_socket_fd);
        printf("socket cerrado. \n");
    }
    exit(0);


}


void llamada_manejar(int socket_fd){
    global_socket_fd=socket_fd;

    if(signal(SIGINT, manejar_control_c)==SIG_ERR){
        perror("Error al llamar el manejo de control c");
        exit(1);
    }


}
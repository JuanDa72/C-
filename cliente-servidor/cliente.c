#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h> // Para bzero
#include "herramientas.h"

#define port 3535

struct sockaddr_in c_addr;

int main (){
    Operativo
    int cliente_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(cliente_fd<0){
        perror("Error al crear el socket");
        exit(1);    
    }   

    c_addr.sin_family=AF_INET;
    c_addr.sin_port=htons(port);
    c_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(c_addr.sin_zero), 8);

    int r=connect(cliente_fd, (struct sockaddr *)&c_addr, sizeof(c_addr));
    if (r<0){
        perror("Error en connect");
        close(cliente_fd);
        exit(1);
    }

    char buffer[21];
    int rec=recv(cliente_fd, buffer, 20, 0);
    if (rec<0){
        perror("Error en recv");
    }

    printf("mensaje: %s", buffer);


    char mensaje[]="Hola servidor \n";

    int s=send(cliente_fd, mensaje, sizeof(mensaje), 0);
    if(s<0){
        perror("Error en send");
    }

    close(cliente_fd);

}
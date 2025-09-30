#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h> // Para bzero
#include "herramientas.h"

#define puerto 3535
#define backlog 4

struct sockaddr_in servidor_addr, cliente_addr;

int main (){
    int servidor_fd;
    //Creación de socket
    
    servidor_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(servidor_fd<0){
        perror("Error al crear el socket");
        exit(1);    
    }

    //Reutilización de puerto
    if(reuse(servidor_fd)<0){
        close(servidor_fd);
        exit(1);
    }

    servidor_addr.sin_family=AF_INET;
    servidor_addr.sin_addr.s_addr=INADDR_ANY;
    servidor_addr.sin_port=htons(puerto);
    bzero(&(servidor_addr.sin_zero), 8);

    int r=bind(servidor_fd, (struct sockaddr *)&servidor_addr, sizeof(servidor_addr));
    if (r<0){
        perror("Error en bind");
        close(servidor_fd);
        exit(1);
    }

    int l=listen(servidor_fd, backlog);
    if(l<0){
        perror("Error en listen");
        close(servidor_fd);
        exit(1);
    }

    int size=sizeof(struct sockaddr_in);
    int fd2=accept(servidor_fd, (struct sockaddr*)&cliente_addr, &size);
    if (fd2<0){
        perror("Error en accept");
        close(servidor_fd);
        exit(1);
    }   

    char mensaje[]="Hola cliente \n";

    int s=send(fd2, mensaje, sizeof(mensaje), 0);
    if(s<0){
        perror("Error en send");
        close(fd2);
    }

    char buffer[21];
    int rec=recv(fd2, buffer, 20, 0);
    if (rec<0){
        perror("Error en recv");
    }

    else{
        buffer[rec]='\0';
        printf("Mensaje recibido: %s \n", buffer);
    }

    close(fd2);
    close(servidor_fd);

    return 0;

}  
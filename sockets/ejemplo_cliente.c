#include <stdio.h> // utilp para printf y perror
#include <stdlib.h> // util para exit
#include <unistd.h> // util para close
#include <sys/socket.h> // util para socket, bind, listen, accept
#include <netinet/in.h> // util para struct sockaddr_in
#include <strings.h> // util para bzero
#include <arpa/inet.h> // util para inet_addr

#define PORT 1717 //Puerto al cual queremos conectarnos :)

struct sockaddr_in c_addr;

int main(){

    int client_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd<0){
        perror("Error al crear el socket");
        exit(1);    
    }

    c_addr.sin_family=AF_INET;
    c_addr.sin_port=htons(PORT);
    c_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(c_addr.sin_zero), 8);

    int r=connect(client_fd, (struct sockaddr *)&c_addr, sizeof(c_addr));

    if (r<0){
        perror("Error en connect");
        close(client_fd);
        exit(1);
    }

    char buffer[21];
    int rec=recv(client_fd, buffer, 20, 0);
    if (rec<0){
        perror("Error en recv");
        close(client_fd);
        exit(1);
    }

    printf("mensaje: %s", buffer);
    char mensaje[]="Hola servidor \n";
    int s=send(client_fd, mensaje, sizeof(mensaje), 0);

    if(s<0){
        perror("Error en send");
    }
    close(client_fd);
    return 0;

}
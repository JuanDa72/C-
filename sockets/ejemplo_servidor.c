#include <stdio.h> // utilp para printf y perror
#include <stdlib.h> // util para exit
#include <unistd.h> // util para close
#include <sys/socket.h> // util para socket, bind, listen, accept
#include <netinet/in.h> // util para struct sockaddr_in
#include <strings.h> // util para bzero
#include <arpa/inet.h> // util para inet_addr

//Ejercicio basico: Servidor acepta conexión y la reenvía con algun cambio. 
#define PORT 1717
#define BACKLOG 4 //Número máximo de conexiones pendientes

struct sockaddr_in server_addr, client_addr;

int main(){
    int server_fd;

    //Para crear el protocolo le pasamos:
    //1. Dominio: AF_INET (IPv4) podría ser AF_INET6 (IPv6) o AF_UNIX (Sockets de dominio Unix)
    //2. Tipo de socket: SOCK_STREAM (orientado a conexión, TCP) o SOCK_DGRAM (no orientado a conexión, UDP)
    //3. Protocolo: 0 (automático, en función del tipo de socket)
    server_fd=socket(AF_INET, SOCK_STREAM, 0);



    server_addr.sin_family=AF_INET; //Indicamos que espera ipv4, debe coincidir con el dominio del socket
    server_addr.sin_addr.s_addr=INADDR_ANY; //Acepta conexiones de cualquier IP
    server_addr.sin_port=htons(PORT); //Puerto en el que escucha el servidor
    bzero(&(server_addr.sin_zero), 8); //Rellenar con ceros

    //Bind
    int r=bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (r<0){
        perror("Error en bind");
        close(server_fd);
        exit(1);
    }

    int l=listen(server_fd, BACKLOG);
    if(l<0){
        perror("Error en listen");
        close(server_fd);
        exit(1);
    }

    int size=sizeof(struct sockaddr_in);
    int fd2=accept(server_fd, (struct sockaddr*)&client_addr, &size);
    if (fd2<0){
        perror("Error en accept");
        close(server_fd);
        exit(1);
    }

    char mensaje[]="Hola cliente \n";

    int s=send(fd2, mensaje, sizeof(mensaje), 0);
    if(s<0){
        perror("Error en send");
        close(fd2);
    }

    //Buffer para recibir mensajes, asumimos que no supera 20 caracteres
    char buffer[21];

    int rec=recv(fd2, buffer, 20, 0); //socket, buffer, longitud, flags
    //Devuelve la cantidad de bytes recibidos
    if (rec<0){
        perror("Error en recv");
    }

    else {
        buffer[rec]='\0'; //Aseguramos el fin de cadena
        printf("Mensaje recibido: %s\n", buffer);
    }

    close(fd2);
    close(server_fd);

    return 0;

}
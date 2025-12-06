#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1" // Localhost
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // 1. CREAR SOCKET
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error creación socket");
        return -1;
    }

    // 2. DEFINIR DIRECCIÓN DEL SERVIDOR
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir IP de texto a binario
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Dirección inválida / No soportada");
        return -1;
    }

    // 3. CONECTAR (Connect)
    printf("Intentando conectar a %s:%d...\n", SERVER_IP, PORT);
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Conexión fallida");
        return -1;
    }
    printf("--> Conectado al servidor.\n");

    //
    
    char *hello = "Hola desde el cliente";
    send(sock_fd, hello, strlen(hello), 0);
    printf("Mensaje enviado.\n");

    // Ejemplo: Recibir respuesta
    ssize_t valread = read(sock_fd, buffer, BUFFER_SIZE - 1);
    if (valread > 0) {
        buffer[valread] = '\0'; // Asegurar null-termination
        printf("Respuesta del servidor: %s\n", buffer);
    }

    //

    close(sock_fd);
    return 0;
}
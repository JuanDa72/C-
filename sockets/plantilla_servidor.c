#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 5
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int opt = 1;

    // 1. CREAR SOCKET
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error en socket");
        exit(EXIT_FAILURE);
    }

    // 2. CONFIGURAR SOCKET (REUSEADDR) - ¡Truco para exámenes!
    // Esto permite volver a ejecutar el servidor inmediatamente tras cerrarlo.
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Error en setsockopt");
        exit(EXIT_FAILURE);
    }

    // 3. DEFINIR DIRECCIÓN DEL SERVIDOR
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Escuchar en cualquier IP
    server_addr.sin_port = htons(PORT);       // Puerto (con conversión de endian)

    // 4. BIND (Ligar puerto)
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error en bind");
        exit(EXIT_FAILURE);
    }

    // 5. LISTEN (Escuchar)
    if (listen(server_fd, BACKLOG) < 0) {
        perror("Error en listen");
        exit(EXIT_FAILURE);
    }

    printf("--> Servidor ESCUCHANDO en puerto %d...\n", PORT);

    while (1) {
        printf("--> Esperando conexión...\n");
        
        if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
            perror("Error en accept");
            continue; 
        }
        
        printf("--> Cliente conectado desde %s:%d\n", 
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        
        
        char buffer[BUFFER_SIZE] = {0};
        ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        
        if (bytes_read > 0) {
            printf("Mensaje del cliente: %s\n", buffer);
            
            // Ejemplo: Enviar respuesta
            char *msg = "Recibido OK";
            send(client_fd, msg, strlen(msg), 0);
        }
        
        //

        close(client_fd); // Cerrar socket del cliente actual
        printf("--> Conexión cerrada con el cliente.\n");
    }

    return 0;
}
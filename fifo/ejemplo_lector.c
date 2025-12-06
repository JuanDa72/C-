#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>    // Para las banderas de archivo O_RDONLY
#include <sys/stat.h> // Necesario si queremos usar mkfifo aquí también
#include <unistd.h>   // Para read

#define FIFO_FILE "/tmp/mi_fifo"
#define BUFFER_SIZE 100

int main(){
    int fd;
    char buffer[BUFFER_SIZE];

    //Abrir el fifo en modo lectura
    fd=open(FIFO_FILE, O_RDONLY);
    if(fd == -1){
        perror("Error al abrir el FIFO para lectura");
        return 1;
    }

    ssize_t bytes_read=read(fd, buffer, sizeof(buffer));
    if(bytes_read == -1){
        perror("Error al leer del FIFO");
        close(fd);
        return 1;
    }
    printf("Mensaje recibido: %s\n", buffer);
    close(fd);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // para banderas
#include <sys/stat.h>   // mkfifo
#include <unistd.h>    // para write, read, close

#define FIFO_NAME "/tmp/mi_fifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char mensaje[]="Hola desde un proceso no emparentado";

   //Creación del fifo
   if(mkfifo(FIFO_NAME, 0666) == -1){
       perror("Error al crear el FIFO");   
    }

    //Abrir el FIFO para escritura
    //EL O_WRONLY indica que es solo para escritura
    fd = open(FIFO_NAME, O_WRONLY);
    if(fd == -1){
        perror("Error al abrir el FIFO para escritura");
        return 1;
    }

    //Escribir el mensaje en el FIFO
    
    //Primero hay que saber exactamente el tamaño xd
    size_t len=strlen(mensaje)+1; //+1 para el caracter nulo
    if(write(fd, mensaje, len) == -1){
        perror("Error al escribir en el FIFO");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;

    //Podriamos poner un unlink para eliminar el fifo
    //unklink(FIFO_NAME);
    

}
#include <sys/types.h>
#include <sys/stat.h>   // Para mkfifo() y modos de archivo
#include <unistd.h>
#include <fcntl.h>      // Para open()
#include <stdio.h>


int main(){

    int fd=open("first_fifo", O_RDONLY);

    int number;

    read(fd, &number, sizeof(number));

    number*=2;

    printf("El número leído del FIFO es %d\n", number);

    close(fd);
    unlink("first_fifo");
    return 0;
}
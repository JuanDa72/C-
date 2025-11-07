#include <sys/types.h>
#include <sys/stat.h>   // Para mkfifo() y modos de archivo
#include <unistd.h>
#include <fcntl.h>      // Para open()
#include <stdio.h>


int main(){

    mkfifo("first_fifo", 0666);

    int fd=open("first_fifo", O_WRONLY);

    int number=5;

    write(fd, &number, sizeof(number));

    close(fd);
    return 0;

}


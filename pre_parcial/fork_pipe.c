//Crear un pipe que envíe un número y el hijo lo multiplique por 2
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
//Crear pipe antes que el fork
int pipe_fd[2];

int r=pipe(pipe_fd);

if(r<0){
	perror("Error al crear el pipe");
}

pid_t pid=fork();
int recv;

if(pid<0){
	perror("Error al realizar el fork");
}

else if(pid==0){
	close(pipe_fd[0]);
	int number=5;
	r=write(pipe_fd[1] ,&number, sizeof(number));
	close(pipe_fd[1]);	
}

else{
	close(pipe_fd[1]);
	r=read(pipe_fd[0], &recv, sizeof(recv));
	recv*=2;

	printf("El número despues de multiplicar es %d", recv);
	close(pipe_fd[0]);
	wait(NULL); 
	return 0;
}

    
}

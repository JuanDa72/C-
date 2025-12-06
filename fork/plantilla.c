#include <stdio.h>    // Entrada/Salida: printf, perror
#include <stdlib.h>   // Utilidades: exit, EXIT_SUCCESS/FAILURE
#include <unistd.h>   // Llamadas al sistema: fork, getpid, getppid
#include <sys/types.h> // Tipos: pid_t
#include <sys/wait.h>  // Espera: wait

#define EXIT_CODE 42 // Define un código de salida específico para el hijo

int main() {
    pid_t pid;

    // 1. Llamada a fork() para duplicar el proceso
    pid = fork();
    
    // --- MANEJO DE ERRORES ---
    if (pid < 0) {
        perror("ERROR: Falló la creación del proceso hijo");
        return EXIT_FAILURE; // Retorna 1
    } 
    
    // --- LÓGICA DEL PROCESO HIJO ---
    else if (pid == 0) {
        // Bloque ejecutado ÚNICAMENTE por el proceso hijo.
        
        printf("--- HIJO ---\n");
        printf("Soy el Proceso Hijo.\n");
        printf("Mi PID es: %d\n", getpid());
        printf("Mi Padre tiene el PID: %d\n", getppid());
        
        // **********************************
        // AÑADE AQUÍ EL CÓDIGO ESPECÍFICO DEL HIJO
        // **********************************
        
        printf("Hijo: Termino mi ejecución con el código %d.\n", EXIT_CODE);
        exit(EXIT_CODE); // El hijo debe salir al terminar su tarea.
    } 
    
    // --- LÓGICA DEL PROCESO PADRE ---
    else {
        // Bloque ejecutado ÚNICAMENTE por el proceso padre.
        // 'pid' aquí contiene el PID del hijo.
        int status; // Variable para almacenar el estado de terminación del hijo.

        printf("--- PADRE ---\n");
        printf("Soy el Proceso Padre.\n");
        printf("Mi PID es: %d\n", getpid());
        printf("El PID de mi hijo es: %d\n", pid);

        // **********************************
        // AÑADE AQUÍ EL CÓDIGO ESPECÍFICO DEL PADRE (p.ej., wait, pipes, etc.)
        // **********************************
        
        // 2. Esperar al proceso hijo para evitar procesos zombie
        printf("Padre: Esperando la terminación del hijo...\n");
        if (wait(&status) == -1) {
            perror("ERROR: Falló al esperar al hijo");
        } else {
            // Analizar el estado de terminación del hijo
            if (WIFEXITED(status)) {
                printf("Padre: El hijo terminó normalmente. Código de salida: %d\n", WEXITSTATUS(status));
            } else {
                printf("Padre: El hijo terminó de forma anormal.\n");
            }
        }
        
        printf("Padre: Finalizo mi ejecución.\n");
    }

    return EXIT_SUCCESS; // El padre termina de forma exitosa.
}
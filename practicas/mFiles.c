#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(){

    //Puntero
    FILE *fptr;
    //Abrir un archivo
    fptr = fopen("test.txt", "w");
    if(fptr != NULL){
        printf("File opened successfully\n");
        fprintf(fptr,"Escribiendo cualquier cosa");
        fclose(fptr);
    }
    else{
        printf("Error opening file\n");
        return 1; // Salir si no se puede abrir el archivo
    }

    return 0;

}

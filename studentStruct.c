#include <stdio.h>
#include <stdbool.h>

struct Estudiante {

    char nombre[50];
    int edad;
    float promedio;

    
};

int main(){
    struct Estudiante estudiante1;

    //Podemos asginarle valores a los miebros facilmente 
    //Para el nombre podemos usar tnato strcpy como snprintf

    snprintf(estudiante1.nombre, sizeof(estudiante1.nombre), "Juanito alimaña");
    estudiante1.edad=20;
    estudiante1.promedio=3.5;

    printf("Nombre: %s \n",estudiante1.nombre);
    printf("Edad: %d \n",estudiante1.edad);
    printf("Promedio: %.2f \n",estudiante1.promedio);

    return 0;
}
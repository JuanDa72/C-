#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(){

    int age;
    float gpa;
    char grade;
    char name[30];

    printf("Enter your age: ");
    //Con Scanf es necesario poner como segundo parametro la dirección de la variable
    //en donde queremos guardar el valor ingresado por el usuario
    scanf("%d",&age);

    printf("Enter your GPA: ");
    scanf("%f",&gpa);

    printf("Enter your char: ");
    //Tenemos que agregar un espacio en blnco antes del formato para indicar
    //que ignore cualquier espacio en blanco que haya quedado en el buffer
    scanf(" %c",&grade);

    getchar();

    printf("Enter your name: ");
    //Creo que para String es mejor utilizar fgets, ya que permite el uso de espacios
    //Es necesario poner el tamaño del arreglo, para evitar errores es mejor poner 
    //sizeof(name) que es el tamaño real del arreglo
    //Stdin indica que la entrada es estadar (teclado)
    fgets(name, sizeof(name), stdin);
    //Si queremos eliminar el salto de linea que genera automaticamente fgets
    //Tenemos que usar
    name[strlen(name)-1]='\0';

    printf("\n");

    printf("Your name is %s \n",name);
    printf("You are %d years old\n",age);
    printf("%.2f \n",gpa);
    printf("%c \n",grade);


    

    return 0;
}

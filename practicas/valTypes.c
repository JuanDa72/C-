//Agregar esto permite usar la funcion printf y scanf
#include <stdio.h>
//Agregar esto permite usar booleanos de forma mas "sencilla"
#include <stdbool.h>

//Probando las variables de c 

int main() {
    

    //Enteros
    int age=25;
    int year=2025;
    int quantity=1;

    //Flotantes
    float gpa=2.5;
    float price=19.99;
    float temperature=-10.1;

    //Double precision
    double pi=3.141592653589793;

    //Chars
    char grade='A';
    char symbol='!';
    char currency='$';

    //Arreglos char
    char name[]="juan";
    char food[]="pizza";
    char email[]="jcruzgi@unal.edu.co";

    //Booleanos
    //Estan representados como 1 y 0, false es 0 y true es 1
    bool isOnline=true;

    //Impresiones int 
    printf("you are %d years old \n", age);
    printf("the year is %d \n", year);
    printf("you have ordered %d x items \n",quantity);

    //Imprsiones float 
    printf("your gpa is %f \n",gpa);
    printf("the price is $%f \n",price);
    printf("the temperature is %f\n",  temperature);

    //Impresiones double
    //Podemos especificar rapidamente cuantos digitos queremos
    printf("the value of pi is %.8lf \n",pi);

    //Impresiones char 
    printf("your grade is %c \n",grade);
    printf("your favourite symbol is %c \n",symbol);
    printf("the currency is %c \n",currency);
    
    //Impresiones char array
    printf("Hello %s \n",name);
    printf("your favourite food is %s \n",food);
    printf("your email is %s \n",email);

    //impresiones booleanas
    //Podemos imprimir el valor númerico que representa el booleano
    printf("%d \n",isOnline);

    //--------------------------------------------------------

    //Podmemos definir el width de un printf, es decir la cantidad de espacios que queremos ver 
    //No confundir con la precisión 
    //Para definir el ancho ponemos un número entre el % y la letra que define el tipo de dato

    //Ejemplos
    int num4=1000;
    int num5=-14594;
    printf("%5d \n",num4);
    //La impresión debeería de estar desplazada 1 espacio
    
    //Tambien podemos definir si queremos números en lugar de espacios en blanco
    printf("%05d \n",num4);

    //O tambien pueden ser simbolos xd
    printf("%+d \n",num5);


    //Tambien podemos definir la precisión como vimos en un ejemplo anterior xd
    float price5=1043.450000;
    printf("the price is %.2f \n",price5);

    //Combinando el witdh y la precisión
    printf("the price with + is %5.2f \n",price5);


    return 0;
}
#include <stdio.h>
#include <string.h>

int main(){

    char name[51];
    char adjective[51];
    char verb[51];

    printf("Enter a name: ");
    //No olvidar los parametros para fgets, recuerda que el primero es un puntero
    //EL segundo es el tamño, y el último puede ser tanto stdin si es consola
    //como el puntero al arhivo tipo ftlr o algo así.
    fgets(name, sizeof(name), stdin);
    name[strlen(name)-1] = '\0'; //Remueve el salto de linea

    printf("Enter an adjetive: ");
    fgets(adjective, sizeof(adjective), stdin);
    adjective[strlen(adjective)-1] = '\0'; //Remueve el salto de linea


    printf("Enter a verb: ");
    fgets(verb, sizeof(verb), stdin);
    verb[strlen(verb)-1] = '\0'; //Remueve el salto de linea

    printf("%s \n",name);
    printf("%s \n",adjective);
    printf("%s \n",verb);

    return 0;
}
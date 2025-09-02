#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "/home/juanda/Documentos/c/so1/personStructure.h"


int main(){

    struct Person person1;
    printf("Enter name: ");
    fgets(person1.name, sizeof(person1.name), stdin);
    person1.name[strlen(person1.name)-1]='\0';

    printf("Enter last name: ");
    fgets(person1.lastName, sizeof(person1.lastName), stdin);
    person1.lastName[strlen(person1.lastName)-1]='\0';

    printf("Enter age: ");
    scanf("%d",&person1.age);

    printf("Enter stature: ");
    scanf("%f",&person1.stature);

    FILE *fptr;
    fptr=fopen("person.txt","w");
    if(fptr != NULL){
        fprintf(fptr, "%s \n",person1.name);
        fprintf(fptr, "%s \n", person1.lastName);
        fprintf(fptr, "%d \n", person1.age);
        fprintf(fptr, "%.2f\n",person1.stature);
    }

}


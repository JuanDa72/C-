#include <stdio.h>
#include <stdbool.h>
#include "/home/juanda/Documentos/c/so1/personStructure.h"
#include <string.h>

int main(){

    struct Person person1;
    FILE *fptr;
    fptr=fopen("person.txt","r");
    if(fptr!=NULL){
        fgets(person1.name,sizeof(person1.name),fptr);
        person1.name[strlen(person1.name)-1]='\0';
        fgets(person1.lastName,sizeof(person1.lastName),fptr);
        person1.lastName[strlen(person1.lastName)-1]='\0';

        fscanf(fptr, "%d", &person1.age);
        fscanf(fptr, "%f",&person1.stature);

        printf("Name: %s\n", person1.name);
        printf("Last name: %s\n", person1.lastName);
        printf("Age: %d\n", person1.age);
        printf("Stature: %.2f\n", person1.stature);
        

        fclose(fptr);

        return 0;
    }

    else{
        printf("Error opening file\n");
        return 1;
    }



}
    
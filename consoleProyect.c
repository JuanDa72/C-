#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(){

    //Variables
    char item[50];
    float price;
    int quantity;
    char currency='$';
    float total;

    printf("What item would you like to buy? ");
    fgets(item, sizeof(item), stdin);

    printf("What is the price for each?" );
    scanf("%f",&price);

    printf("How many would you like? ");
    scanf("%d", &quantity);

    printf("\n");
    total=price*quantity;  
    printf("You have bought %d %s",quantity,item);
    printf("the total is %c%.2f",currency,total);


    return 0;
}
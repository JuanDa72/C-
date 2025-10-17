#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define size 1000

struct node {
    long offset; // Offset en el archivo binario
    long nextOffset; // Offset del siguiente nodo en la lista enlazada
};

struct node setNode(long offset, long nextOffset){

    struct node node;

    node.offset = offset;
    node.nextOffset = nextOffset;
    return node; 

}


struct hashTable{

    struct node buckets[size];
};


int hashFunction(const char *artista){
    unsigned int hash = 0;
    while (*artista) {
        hash = hash * 31 + tolower(*artista++);
    }
    return hash % 1000;
}


void initializeHashTable(struct hashTable* table) {

    // Inicializar todos los buckets como vacíos
    for (int i = 0; i < size; i++) {
        table -> buckets[i] = setNode(-1, -1); // Usar -1 para indicar que el bucket está vacío
    }
}


void insert(struct hashTable* table, char* artist, long offset) {

    int position=hashFunction(artist);

    struct node node=table -> buckets[position];

    if(node.offset == -1) {
        // El bucket está vacío, insertar el nuevo nodo aquí
        table->buckets[position].offset = offset;
        table->buckets[position].nextOffset = -1; // No hay siguiente nodo
    }
    
    else {
        // El bucket ya tiene un nodo
        
        //Creamos un nuevo nodo
        //Ahora el nuevo nodo es la cabeza
        struct node current=setNode(offset, node.offset);

        table->buckets[position].offset = current.offset;
        table->buckets[position].nextOffset = current.nextOffset;

    }


}


struct node search(struct hashTable* table, const char* artist) {

    int index = hashFunction(artist);
    struct node head=table->buckets[index];

    return head;

}
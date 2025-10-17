#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nodeAndHastTable.h"
#include "songStruct.h"
#include <stdbool.h>
#include <unistd.h>

struct hashTable writeHashTable(const char* songFile){

    FILE* fSongs=fopen(songFile, "r+b");
    if(!fSongs){
        perror("Error al abrir el archivo de canciones");

        //Igual toca retornar algo 
        struct hashTable table;
        initializeHashTable(&table);
        return table;
    }

    //Creando la tabla hash
    struct hashTable table;
    initializeHashTable(&table);


    struct Song song;

    //Leer cada canción y agregarla a la tabla hash
    while (fread(&song, sizeof(song), 1, fSongs) == 1) {

        printf("\n");
        printf("Procesando canción %s\n", song.name);
        long originalOffset=ftell(fSongs) - sizeof(song); // Offset de la canción recién leída
        printf("Offset de la canción: %ld\n", originalOffset);
        //sleep(5);



        struct node existingNode = search(&table, song.artist);

        if (existingNode.offset == -1) {
            printf("No existe colision\n");
            //sleep(5);
            // No hay colisión, insertar directamente
            insert(&table, song.artist, originalOffset);
        } 

        else {


            if (existingNode.nextOffset == -1) {

                printf("Existe una única colisión\n");
                //sleep(5);
                // Solo se tiene una canción con ese hash
                insert(&table, song.artist, originalOffset);

            }

            else {

                printf("Existen múltiples colisiones\n");
                printf("\n");
                //sleep(5); 

                //Hay por lo menos dos canciones con ese hash
                //Es necesario actualizar el campo nextOffset de la canción que actualmente es la cabeza

                //Canción a la que apunta el nodo actual
                struct Song currentSong;

                //Obtenemos la estructura de la canción completa
                //Por lo que nos devolvemos el offset guardado en el nodo
                fseek(fSongs, existingNode.offset, SEEK_SET);
                fread(&currentSong, sizeof(currentSong), 1, fSongs);

                long offset=ftell(fSongs) - sizeof(song); // Offset de la canción recién leída

                printf("Offset de la canción despues de devolvernos: %ld\n", offset);

                printf("Actualizando la canción que actualmente es la cabeza: ");
                printf(currentSong.name);
                //sleep(5);
                printf("\n");

                //Cambiamos el campo nextOffset
                currentSong.nextOffset = existingNode.nextOffset;
                printf("Nuevo nextOffset de la canción %s: %ld\n", currentSong.name, currentSong.nextOffset);

                //Escribimos la canción actualizada en el archivo
                fseek(fSongs, existingNode.offset, SEEK_SET);
                printf("En este punto nos encontramos en el offset: %ld\n", ftell(fSongs));
                printf("\n");


                fwrite(&currentSong, sizeof(currentSong), 1, fSongs);
                printf("Despues de escrbir nos encontramos en el offset: %ld\n", ftell(fSongs));


                //Insertamos en la tabla hash el nuevo head
                insert(&table, song.artist, originalOffset);
                fseek(fSongs, originalOffset+sizeof(currentSong), SEEK_SET);
                printf("Saltamos a la siguiente canción: %ld\n", ftell(fSongs));
                printf("\n");
            }

        
        }

    }


    fclose(fSongs);

    return table;


}


int main(){

    //Llamamos a la función para crear la tabla hash
    struct hashTable table=writeHashTable("songs.bin");

    //Guardamos la tabla hash en un binario 
    FILE * hastTableSongs = fopen("hashTableSongs.bin", "wb");
    if(!hastTableSongs){
        perror("Error al crear el archivo binario de la tabla hash");
        return 1;   
    }

    fwrite(&table, sizeof(struct hashTable), 1, hastTableSongs);
    fclose(hastTableSongs);
    
    return 0;

}
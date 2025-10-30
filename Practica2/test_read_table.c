#include <stdio.h>
#include "songStruct.h"
#include <string.h>
#include "nodeAndHastTable.h"


//Pasa una cadena a minúsculas
void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}


struct Song searchSong(const char* artistName, const char* songName) {

    struct Song song;
    
    //Usamos memset para inicializar la estructura en 0
    memset(&song, 0, sizeof(song));

    struct hashTable table;

    //Abrimos el archivo de la tabla hash
    FILE* fHash=fopen("hash_test_table.bin","rb");

    //Verificamos
    if(!fHash){
        perror("Error al abrir la tabla hash");
        return song;
    }

    fread(&table, sizeof(table),1, fHash);
    fclose(fHash);

    struct node head=search(&table, artistName);
    if(head.offset==-1){
        printf("No tenemos coincidencias");
        strcpy(song.artist, "NA");
        strcpy(song.name, "No hay coincidiencias de canciones con este autor");
        return song;
    }


    FILE* fSongs=fopen("songs_hash_test.bin","rb");
    if(!fSongs){
        perror("Error al abrir el binario de las canciones");
        return song;
    }

    long offset=head.offset;
    int flag=0; //Para que en la primera comparación miremos el offset
    // y el nextoffset del head.

    //Recorremos las canciones hasta encontrar la coincidencia exacta
    while(offset!=-1){
        
        fseek(fSongs, offset, SEEK_SET);
        fread(&song, sizeof(song), 1, fSongs);
        //printf("Actualmente leyendo %s \n", song.name);

        if(strcmp(artistName, song.artist)==0 && strcmp(songName, song.name)==0){
            printf("Encontramos algo \n");
            fclose(fSongs);
            return song;
        }

        if(flag==0){
            printf("primera comparación \n");
            offset=head.nextOffset;
            flag=1;
        }

        else{
            offset=song.nextOffset;
        }
    }

    strcpy(song.artist, "NA");
    strcpy(song.name, "No hay coincidiencia de alguna canción con este autor y este nombre");
    fclose(fSongs);
    return song;

}


int main(){

    char artist[100] = "Juanda & Gemini 6";
    char name[300]="El Código Perfecto";

    // Llamamos a tu función
    struct Song result = searchSong(artist, name);

    // Mostramos los resultados
    printf("Artista: %s\n", result.artist);
    printf("Letra: %s\n", result.text);
    printf("Nombre: %s\n", result.name);
    printf("Duracion: %s\n", result.length);
    printf("Genero: %s\n", result.genre);
    printf("Genero: %s\n", result.album);
    printf("Fecha: %s\n\n", result.date);
    printf("Offset: %ld\n\n", result.nextOffset);

    return 0;

}
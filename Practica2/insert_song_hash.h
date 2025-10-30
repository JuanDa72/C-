#include "songStruct.h"
#include <stdio.h>
#include <string.h>
#include "nodeAndHastTable.h"
#include <unistd.h>
#include "insert_song_data_bin.h"


int insert_song_hashT(const char *artistName, const char *songName, struct Song* cancion, long offset) {


    struct hashTable *table =
        (struct hashTable *)malloc(sizeof(struct hashTable));
    if (!table) {
        perror("Error al asignar memoria para tabla hash");
        return -1;
    }

    FILE *fHash = fopen("hashTableSongs.bin", "rb");
    if (!fHash) {
        perror("Error al abrir la tabla hash");
        return -1;
    }

    fread(table, sizeof(struct hashTable), 1, fHash);
    fclose(fHash);

    struct node head = search(table, artistName);
    if (head.offset == -1 || head.nextOffset==-1) {
        //No hay ninguna cancion con este hash o solamente una.
        printf("No tenemos colisiones o solamente tenemos una");
        insert(table, artistName, offset);
    }

    else{

        FILE* fSongs=fopen("songs.bin", "r+b");
        printf("Tenemos colisión importante xd");
        //Hay al menos dos canciones con este hash 

        //Cancion a la que apunta el node offset
        struct Song currentSong;
        fseek(fSongs, head.offset, SEEK_SET);
        fread(&currentSong, sizeof(currentSong), 1, fSongs);

        //Cambiar el campo nextoffset
        currentSong.nextOffset=head.nextOffset;

        //Escribimos en el binario
        fseek(fSongs, head.offset, SEEK_SET);
        fwrite(&currentSong, sizeof(currentSong), 1, fSongs);

        //Insertamos en la tabla hash jijo jijo
        insert(table, artistName, offset);
        fclose(fSongs);
    }

    
    FILE *fHashOut = fopen("hashTableSongs.bin", "wb");
    if (!fHashOut) {
        perror("Error al escribir la tabla hash");
        free(table);
        return -1;
    }

    fwrite(table, sizeof(struct hashTable), 1, fHashOut);
    fclose(fHashOut);

    free(table);
    return 0;

}



long get_last_song_offset() {
    FILE *file = fopen("songs.bin", "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo binario");
        return -1;
    }
    
    // Ir al final del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);
    
    // Si el archivo está vacío
    if (file_size == 0) {
        printf("El archivo está vacío\n");
        return 0;  // o -1 dependiendo de tu lógica
    }
    
    // Calcular offset de la última canción
    long last_song_offset = file_size - sizeof(struct Song);
    
    return last_song_offset;
}

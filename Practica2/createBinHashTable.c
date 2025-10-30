#include "nodeAndHastTable.h"
#include "songStruct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct hashTable writeHashTable(const char *songFile) {

    FILE *fSongs = fopen(songFile, "r+b");
    if (!fSongs) {
        perror("Error al abrir el archivo de canciones");

        struct hashTable table;
        initializeHashTable(&table);
        return table;
    }

    struct hashTable table;
    initializeHashTable(&table);

    struct Song song;

    while (fread(&song, sizeof(struct Song), 1, fSongs) == 1) {

        long originalOffset = ftell(fSongs) - sizeof(struct Song);
        printf("Procesando: %s | %s (offset: %ld)\n", song.artist, song.name,
               originalOffset);

        struct node existingNode = search(&table, song.artist);

        if (existingNode.offset == -1) {
            // No hay colisión, insertar directamente
            printf("  No hay colision\n");
            insert(&table, song.artist, originalOffset);
        } else {
            if (existingNode.nextOffset == -1) {
                // Solo hay una canción con ese hash
                printf("  Existe una colision\n");
                insert(&table, song.artist, originalOffset);
            } else {
                // Hay múltiples canciones con ese hash
                printf("  Existen multiples colisiones\n");

                // Leer la canción actual que es la cabeza
                struct Song currentSong;
                fseek(fSongs, existingNode.offset, SEEK_SET);
                fread(&currentSong, sizeof(struct Song), 1, fSongs);

                // Actualizar el nextOffset de la canción actual
                currentSong.nextOffset = existingNode.nextOffset;

                // Escribir la canción actualizada
                fseek(fSongs, existingNode.offset, SEEK_SET);
                fwrite(&currentSong, sizeof(struct Song), 1, fSongs);
                fflush(fSongs);

                // Insertar el nuevo nodo como cabeza
                insert(&table, song.artist, originalOffset);

                // Volver a posicionar el puntero después de la canción actual
                fseek(fSongs, originalOffset + sizeof(struct Song), SEEK_SET);
            }
        }
    }

    fclose(fSongs);
    return table;
}

int main() {
    struct hashTable table = writeHashTable("songs.bin");

    FILE *hashTableSongs = fopen("hashTableSongs.bin", "wb");
    if (!hashTableSongs) {
        perror("Error al crear el archivo binario de la tabla hash");
        return 1;
    }

    fwrite(&table, sizeof(struct hashTable), 1, hashTableSongs);
    fclose(hashTableSongs);

    return 0;
}

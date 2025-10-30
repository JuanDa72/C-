#include "songStruct.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cleanQuotes(char *str) {
    size_t len = strlen(str);

    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

void lineToSong(char *line, struct Song *song) {

    char *token = strtok(line, "|");
    int field = 0;

    while (token) {

        cleanQuotes(token);

        switch (field) {
        case 0:
            strncpy(song->artist, token, ARTIST_MAX);
            break;
        case 1:
            strncpy(song->name, token, NAME);
            break;
        case 2:
            strncpy(song->text, token, TEXT);
            break;
        case 3:
            strncpy(song->length, token, ARTIST_MAX);
            break;
        case 4:
            strncpy(song->emotion, token, ARTIST_MAX);
            break;
        case 5:
            strncpy(song->genre, token, ARTIST_MAX);
            break;
        case 6:
            strncpy(song->album, token, NAME);
            break;
        case 7:
            strncpy(song->date, token, NAME);
            break;
        }

        field++;
        token = strtok(NULL, "|");
    }
}

int main() {

    FILE *fcsv = fopen("spotify_para_c.csv", "r");
    if (!fcsv) {
        perror("Error al abrir el dataset");
        return 1;
    }

    // Binario en donde vamos a escribir las estructuras
    FILE *fbin = fopen("songs.bin", "wb");
    if (!fbin) {
        perror("Error al crear el archivo binario");
        return 1;
    }

    char buffer[15000]; // Para poder leer una linea (No estoy seguro del tamaño
                        // xd)

    struct Song song; // La estructura que creamos en el otro archivo

    fgets(buffer, sizeof(buffer), fcsv); // Leer la primera linea (headers)

    while (fgets(buffer, sizeof(buffer), fcsv)) {

        buffer[strcspn(buffer, "\n")] = '\0';
        lineToSong(buffer, &song);
        song.nextOffset = -1; // Inicializar nextOffset
        fwrite(&song, sizeof(struct Song), 1, fbin);
    }

    fclose(fcsv);
    fclose(fbin);
    return 0;

    /*Prueba para una sola entrada
    if(fgets(buffer, sizeof(buffer), fcsv)){
        buffer[strcspn(buffer, "\n")] = '\0';
        lineToSong(buffer, &song);
        printf("Artista: %s\n", song.artist);
        printf("Nombre: %s\n", song.name);
        printf("Letra: %s\n", song.text);
        printf("Duracion: %s\n", song.length);
        printf("Emocion: %s\n", song.emotion);
        printf("Genero: %s\n", song.genre);
        printf("Album: %s\n", song.album);
        printf("Fecha: %s\n", song.date);
    }

    fclose(fcsv);
    return 0;
*/
}

#include "songStruct.h"
#include <stdio.h>
#include <string.h>
#include "nodeAndHastTable.h"
#include <unistd.h>

#ifndef INSERT_SONG_DATA_BIN_H
#define INSERT_SONG_DATA_BIN_H

// Definición del archivo de datos

int add_song_to_dataset(struct Song *cancion) {
    // Si el archivo no existe, lo crea. Si existe, se posiciona al final.
    FILE *file = fopen("spotify_para_c.csv", "a");

    if (file == NULL) {
        perror("Error al abrir o crear el archivo");
        return -1; // Salir si hay error
    }

    // 2. Formatear la nueva línea de datos
    // Usamos el formato de tu dataset, separando los campos con "|" y el texto
    // con comillas dobles.
    int result = fprintf(
        file,
        "\n\"%s\"|\"%s\"|\"%s\"|\"%s\"|\"%s\"|\"%s\"|\"%s\"|\"%s\"", // Formato
        cancion->artist, cancion->name, cancion->text, cancion->length,
        cancion->emotion, cancion->genre, cancion->album, cancion->date);

    // 3. Verificar si la escritura fue exitosa
    if (result <= 0) {
        perror("Error al escribir los datos en el archivo");
        return -1;
    }
    printf("\nNueva cancion añadida exitosamente al dataset.\n");


    // 4. Cerrar el archivo
    fclose(file);

    return 0;
}


int add_song_to_bin(struct Song *cancion){
    FILE *file=fopen("songs.bin","ab");

    if(file==NULL){
        perror("\nError al abrir o crear el archivo binario de las canciones");
        return -1;
    }



    size_t ew=fwrite(cancion, sizeof(struct Song), 1, file);
    if(ew!=1){
        perror("\nError al insertar la canción al binario");
        return -1;
    }

    fclose(file);
    printf("\nCanción insertada correctamente a binario.");
    return 0;
}


void printSong(const struct Song *song) {
    printf("\n");
    printf("Artista: %s\n", song->artist);
    printf("Canción: %s\n", song->name);
    printf("Duración: %s\n", song->length);
    printf("Emoción: %s\n", song->emotion);
    printf("Género: %s\n", song->genre);
    printf("Álbum: %s\n", song->album);
    printf("Fecha: %s\n", song->date);
    printf("Next Offset: %ld\n", song->nextOffset);
}


int open_song_bin() {
    // 1. Abrir el archivo en modo lectura binaria
    FILE *file = fopen("songs.bin", "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo binario");
        printf("El archivo 'songs_test_server.bin' no existe o no se puede abrir\n");
        return -1;
    }
    
    // 2. Leer la primera canción
    struct Song cancion;
    size_t elements_read = fread(&cancion, sizeof(struct Song), 1, file);
    
    // 3. Cerrar el archivo
    fclose(file);
    
    // 4. Verificar si la lectura fue exitosa
    if (elements_read != 1) {
        if (feof(file)) {
            printf("El archivo está vacío\n");
        } else {
            perror("Error al leer la canción del archivo binario");
        }
        return -1;
    }
    
    // 5. Imprimir la información de la canción
    printSong(&cancion);
    
    return 0;
}

int read_last_song_bin() {
    FILE *file = fopen("songs.bin", "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo binario");
        return -1;
    }
    
    // Obtener el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    
    // Verificar si el archivo está vacío
    if (file_size == 0) {
        printf("El archivo está vacío\n");
        fclose(file);
        return -1;
    }
    
    // Calcular cuántas canciones hay
    long song_count = file_size / sizeof(struct Song);
    //printf("Total de canciones en el archivo: %ld\n", song_count);
    
    // Posicionarse en la última canción
    fseek(file, (song_count - 1) * sizeof(struct Song), SEEK_SET);
    
    // Leer la última canción
    struct Song cancion;
    size_t elements_read = fread(&cancion, sizeof(struct Song), 1, file);
    fclose(file);
    
    if (elements_read != 1) {
        printf("Error al leer la última canción\n");
        return -1;
    }
    
    printf("\n=== ÚLTIMA CANCIÓN AGREGADA ===\n");
    //printSongInfo(&cancion);
    printf("\n");
    printSong(&cancion);
    
    return 0;
}

#endif
#include <stdio.h>
#include "songStruct.h"

int main() {
    FILE *fbinary = fopen("songs.bin", "rb");
    if(!fbinary){
        perror("Error al abrir archivo binario");
        return 1;
    }

    struct Song song;
    int i = 0;
    while(fread(&song, sizeof(struct Song), 1, fbinary)) {

        long offset=ftell(fbinary) - sizeof(song);
        printf("Offset en el archivo: %ld\n", offset);

        printf("Cancion %d:\n", i+1);
        printf("Artista: %s\n", song.artist);
        printf("Letra: %s\n", song.text);
        printf("Nombre: %s\n", song.name);
        printf("Duracion: %s\n", song.length);
        printf("Genero: %s\n", song.genre);
        printf("Album: %s\n", song.album);
        printf("Fecha: %s\n\n", song.date);
        printf("Next Offset: %d\n\n", song.nextOffset);
        

        i++;
        if(i >= 5) break; 
    }

    printf("");
    printf("--------------------\n");

    struct Song song1;
    //Ahora intentar leer una posición en especifico 
    int index = 40;
    printf("Offset en el archivo: %ld\n", index*sizeof(struct Song));   
    fseek(fbinary, index * sizeof(struct Song), SEEK_SET); // salto al inicio de la canción 1000
    fread(&song1, sizeof(struct Song), 1, fbinary);        // leo solo esa canción

    printf("Cancion %d:\n", i+1);
    printf("Artista: %s\n", song1.artist);
    printf("Letra: %s\n", song1.text);
    printf("Nombre: %s\n", song1.name);
    printf("Duracion: %s\n", song1.length);
    printf("Genero: %s\n", song1.genre);
    printf("Album: %s\n", song1.album);
    printf("Fecha: %s\n\n", song1.date);
    printf("NExt Offset: %ld\n\n", song1.nextOffset);


    fclose(fbinary);
    return 0;
}

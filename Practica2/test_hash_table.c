#include "insert_song_server.c"



int insert_song_hashT(const char *artistName, const char *songName, struct Song* cancion, long offset) {


    struct hashTable *table =
        (struct hashTable *)malloc(sizeof(struct hashTable));
    if (!table) {
        perror("Error al asignar memoria para tabla hash");
        return -1;
    }

    FILE *fHash = fopen("hash_test_table.bin", "rb");
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

        FILE* fSongs=fopen("songs_hash_test.bin", "r+b");
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

    
    FILE *fHashOut = fopen("hash_test_table.bin", "wb");
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
    FILE *file = fopen("songs_hash_test.bin", "rb");
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


int main(){


    struct Song cancionDePrueba;
    strcpy(cancionDePrueba.artist, "Juanda & Gemini 6");
    
    // **2. Nombre de la Canción**
    strcpy(cancionDePrueba.name, "El Código Perfecto");
    
    // **3. Letra (Text)**
    // ¡Recuerda! Este texto no debe contener comillas dobles (") ni el delimitador (|)
    strcpy(cancionDePrueba.text, "Si trabajamos juntos, el error se va. Con strcpy y fopen, la solucion llegara.");
    
    // **4. Duración (Length)**
    strcpy(cancionDePrueba.length, "03:45");
    
    // **5. Emoción (Emotion)**
    strcpy(cancionDePrueba.emotion, "satisfaction");
    
    // **6. Género (Genre)**
    strcpy(cancionDePrueba.genre, "programming-pop");
    
    // **7. Álbum (Album)**
    strcpy(cancionDePrueba.album, "Practica Final");
    
    // **8. Fecha (Date)**
    strcpy(cancionDePrueba.date, "28th October 2025");
    
    // **9. nextOffset (No se usa para CSV, pero se inicializa)**
    cancionDePrueba.nextOffset = -1;


    int resultado_csv = add_song_to_dataset(&cancionDePrueba);
    if (resultado_csv == 0) {
        printf("✅ Inserción en CSV exitosa\n\n");
    } else {
        printf("❌ Error en inserción CSV\n\n");
        return -1;
    }

     printf("=== 2. INSERTANDO EN ARCHIVO BINARIO ===\n");
    int resultado_bin = add_song_to_bin(&cancionDePrueba);
    if (resultado_bin == 0) {
        printf("✅ Inserción en binario exitosa\n\n");
    } else {
        printf("❌ Error en inserción binario\n\n");
        return -1;
    }

    //Insertar en tabla hash 
    //Necesitamos calcular el offset xd 

    long offset=get_last_song_offset();

    insert_song_hashT(cancionDePrueba.artist, cancionDePrueba.name, &cancionDePrueba, offset);

    return 0;
}


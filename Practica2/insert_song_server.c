#include "songStruct.h"
#include <stdio.h>
#include <string.h>
#include "nodeAndHastTable.h"
#include <unistd.h>


// Definición del archivo de datos

int add_song_to_dataset(struct Song *cancion) {
    // Si el archivo no existe, lo crea. Si existe, se posiciona al final.
    FILE *file = fopen("prueba_hash.csv", "a");

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
    FILE *file=fopen("songs_hash_test.bin","ab");

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
    FILE *file = fopen("songs_hash_test.bin", "rb");
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
    FILE *file = fopen("songs_hash_test.bin", "rb");
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


//Testing primera función

/*int main(){
    struct Song cancionDePrueba;
    strcpy(cancionDePrueba.artist, "Juanda & Gemini");
    
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

    add_song_to_dataset(&cancionDePrueba);

}*/


//Testing parte del binario
/*
int main(){
    struct Song cancion1 = {
        .artist = "mdmdf",
        .name = "Rjfjfne",
        .text = "They see me..",
        .length = "02:50",
        .emotion = "joy",
        .genre = "rock,pop,comedy",
        .album = "Straight Outta Lynwood",
        .date = "26th September 2006",
        .nextOffset = -1
    };

    add_song_to_bin(&cancion1);
    read_last_song_bin();

}
*/

/*
int main(){
    //Verificnando todo el proceso:
    //1: insertar dataset
    //2: insertar en binario
    //3: insertar en hastable
    //realizar la busqueda xd 


    

}

*/


/*
nt main(){
    printf("=== PRUEBA COMPLETA DEL SISTEMA ===\n\n");
    
    // 1. Crear una canción de prueba
    struct Song cancionPrueba = {
        .artist = "Juanda haciendo el proyecto jijo",
        .name = "El Código Perfecto",
        .text = "Si trabajamos juntos, el error se va. Con strcpy y fopen, la solucion llegara. Los punteros bailan, los structs cantan, en C programamos sin tener lagrimas.",
        .length = "03:45",
        .emotion = "satisfaction", 
        .genre = "programming-pop",
        .album = "Practica Final",
        .date = "28th October 2025",
        .nextOffset = -1
    };
    
    printf("🎵 CANCIÓN CREADA PARA PRUEBA:\n");
    printSong(&cancionPrueba);
    printf("\n");
    
    // 1: INSERTAR EN DATASET (CSV)
    printf("=== 1. INSERTANDO EN DATASET CSV ===\n");
    int resultado_csv = add_song_to_dataset(&cancionPrueba);
    if (resultado_csv == 0) {
        printf("✅ Inserción en CSV exitosa\n\n");
    } else {
        printf("❌ Error en inserción CSV\n\n");
        return -1;
    }
    
    // 2: INSERTAR EN BINARIO
    printf("=== 2. INSERTANDO EN ARCHIVO BINARIO ===\n");
    int resultado_bin = add_song_to_bin(&cancionPrueba);
    if (resultado_bin == 0) {
        printf("✅ Inserción en binario exitosa\n\n");
    } else {
        printf("❌ Error en inserción binario\n\n");
        return -1;
    }
    
    // Verificar que se insertó correctamente en binario
    printf("=== VERIFICANDO INSERCIÓN BINARIA ===\n");
    read_last_song_bin();
    printf("\n");


    //Creación de la tabla hash xd
     struct hashTable table=writeHashTable("songs_test_server.bin");
    FILE * hastTableSongs = fopen("hashTableSongsTest.bin", "wb");
    if(!hastTableSongs){
        perror("Error al crear el archivo binario de la tabla hash");
        return 1;   
    }

    fwrite(&table, sizeof(struct hashTable), 1, hastTableSongs);
    fclose(hastTableSongs);

}
*/


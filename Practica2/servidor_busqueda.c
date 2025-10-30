#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include "insert_song_data_bin.h"
#include "insert_song_hash.h"
#include "nodeAndHastTable.h"
#include "songStruct.h"


#define PORT 3535
#define BACKLOG 4

// Estructura para comunicación entre procesos
struct Comunication {
    // para realizer una busqueda
    char artist[ARTIST_MAX];
    char songName[NAME];
    // para que el cliente envie una canción o que el servidor responda
    struct Song song;
    // flags para la comunicacion
    bool shouldExit;
    bool registrar;
    bool validRegister;
    bool found;
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void printSongInfo(struct Song *song) {
    printf("\n");
    printf("Artista: %s\n", song->artist);
    printf("Cancion: %s\n", song->name);
    printf("Album: %s\n", song->album);
    printf("Genero: %s\n", song->genre);
    printf("Fecha: %s\n", song->date);
    printf("Duracion: %s\n", song->length);
    printf("Emocion: %s\n", song->emotion);
    printf("\nLetra:\n%s\n", song->text);
}

// Función de búsqueda
struct Song searchSong(const char *artistName, const char *songName) {
    struct Song song;
    memset(&song, 0, sizeof(song));

    struct hashTable *table =
        (struct hashTable *)malloc(sizeof(struct hashTable));
    if (!table) {
        perror("Error al asignar memoria para tabla hash");
        strcpy(song.artist, "ERROR");
        return song;
    }

    FILE *fHash = fopen("hashTableSongs.bin", "rb");
    if (!fHash) {
        perror("Error al abrir la tabla hash");
        strcpy(song.artist, "NA");
        strcpy(song.name, "Error al abrir tabla hash");
        free(table);
        return song;
    }

    fread(table, sizeof(struct hashTable), 1, fHash);
    fclose(fHash);

    struct node head = search(table, artistName);
    if (head.offset == -1) {
        strcpy(song.artist, "NA");
        strcpy(song.name, "No hay coincidencias de canciones con este autor");
        free(table);
        return song;
    }

    FILE *fSongs = fopen("songs.bin", "rb");
    if (!fSongs) {
        perror("Error al abrir el binario de las canciones");
        strcpy(song.artist, "NA");
        free(table);
        return song;
    }

    long offset = head.offset;
    int flag = 0;

    while (offset != -1) {
        fseek(fSongs, offset, SEEK_SET);
        fread(&song, sizeof(song), 1, fSongs);

        if (strcmp(artistName, song.artist) == 0 &&
            strcmp(songName, song.name) == 0) {
            fclose(fSongs);
            free(table);
            return song;
        }

        if (flag == 0) {
            offset = head.nextOffset;
            flag = 1;
        } else {
            offset = song.nextOffset;
        }
    }

    strcpy(song.artist, "NA");
    strcpy(
        song.name,
        "No hay coincidencia de alguna canción con este autor y este nombre");
    fclose(fSongs);
    free(table);
    return song;
}


int sendAll(int fd, void *buf, size_t len) {
    size_t total = 0;
    size_t bytes_left = len;
    int n;

    while (total < len) {
        n = send(fd, buf + total, bytes_left, 0);
        if (n == -1) {
            perror("send error");
            return -1;
        }
        total += n;
        bytes_left -= n;
    }
    return 0;
}

int recvAll(int fd, void *buf, size_t len) {
    size_t total = 0;
    size_t bytes_left = len;
    int n;

    while (total < len) {
        n = recv(fd, buf + total, bytes_left, 0);
        if (n == -1) {
            perror("recv error");
            return -1;
        }
        if (n == 0) {
            printf("Cliente desconectado.\n");
            return -1;
        }
        total += n;
        bytes_left -= n;
    }
    return 0;
}

int main() {
    int fd, fd2, r;
    struct sockaddr_in server, client;
    socklen_t size;
    struct Comunication comunicacion;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1) {
        perror("error al crear el socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    memset(&(server.sin_zero), 0, 8);

    r = bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));
    if (r == -1) {
        perror("bind error");
        close(fd);
        exit(1);
    }

    r = listen(fd, BACKLOG);
    if (r == -1) {
        perror("listen error");
        close(fd);
        exit(1);
    }
    printf("Servidor TCP escuchando en puerto %d...\n", PORT);

    size = sizeof(struct sockaddr_in);

    // Bucle principal del servidor
    while (1) {
        // Esperar solicitud
        fd2 = accept(fd, (struct sockaddr *)&client, &size);
        if (fd2 == -1) {
            perror("accept error");
            close(fd);
            exit(1);
        }
        printf("Cliente conectado desde %s:%d\n", inet_ntoa(client.sin_addr),
               ntohs(client.sin_port));
        while (1) {
            // recibir solicitud respuesta
            r = recvAll(fd2, &comunicacion, sizeof(struct Comunication));

            if (r == 0) {
                // por si se termina la ejecución
                if (comunicacion.shouldExit == true) {
                    printf("\ncliente desconectado\n");
                    close(fd2);
                    break;
                }
                // por si se registró una canción
                if (comunicacion.registrar == true) {
                    printf("Entrando a la sección de agregar canciones (servidor) \n");

                    //Probando que si se se devolvio algo de lo que esperabamos xd 
                    //printf(comunicacion.song.date);

                    r = add_song_to_dataset(&comunicacion.song);
                    //printf("\nImprimiuendo cualquier coasa");
                    
                    if (r == -1) {
                        perror("Error al ingresar la canción\n");
                        continue;
                    }

                    //Ahora agregar al binario xd
                    //Solamente llamamos al metodo de insert_song_server y ya xd
                    int r=add_song_to_bin(&comunicacion.song);
                    if(r==-1){
                        perror("Error al escribir la canción en el binario");
                        continue;
                    }

                    //Vamos a leer el binario para saber si se inserto la canción
                    read_last_song_bin();
                    //Funciono correctamente (creo)

                    //Ahora tenemos que insertar esta canción en la tabla hash xd
                    long offset=get_last_song_offset();

                    insert_song_hashT(comunicacion.song.artist, comunicacion.song.name, &comunicacion.song, offset);



                    comunicacion.validRegister = true;
                    printf("\n Ahora responde el servidor");
                    r = sendAll(fd2, &comunicacion, sizeof(comunicacion));

                    if (r == -1) {
                        perror("Error enviando canción\n");
                    }
                } else {

                    printf("buscando: '%s' - '%s'\n", comunicacion.artist,
                           comunicacion.songName);
      
                    comunicacion.song =searchSong(comunicacion.artist, comunicacion.songName);
                    printf("Imprimiendo el nombre que devuelve xd");
                    printf(comunicacion.song.name);

                    comunicacion.found =(strcmp(comunicacion.song.artist, "NA") != 0);

                    r = sendAll(fd2, &comunicacion, sizeof(comunicacion));

                    if (r == -1) {
                        perror("Error enviando canción\n");
                    }
                }
            } else {
                perror("Error reciviendo datos\n");
            }
        }
    }

    close(fd);

    printf("proceso de busqueda terminado\n");
    return 0;
}

#include "songStruct.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

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

void printMenu() {
    printf("\n");
    printf("Bienvenido\n");
    printf("1. Buscar\n");
    printf("2. Registrar una nueva canción\n");
    printf("3. Ingresar criterios de búsqueda\n");
    printf("4. Salir\n");
    printf("Opcion: ");
}

void printSubMenu() {
    printf("\n");
    printf("Ingrese el numero del criterio de busqueda\n");
    printf("1. Ingresar artista\n");
    printf("2. Ingresar canción\n");
    printf("3. Regresar\n");
    printf("Opcion: ");
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

bool isValidString(const char *str, size_t maxSize) {
    return str != NULL && strlen(str) > 0 && strcmp(str, "") != 0 &&
           strlen(str) <= maxSize;
}

// Verifica que la fecha sea valida
bool isValidDate(const char *date) {
    if (date == NULL || strlen(date) < 8)
        return false;

    // Variables para contar componentes
    int dayPart = 0, monthPart = 0, yearPart = 0;
    char day[10] = "", month[20] = "", year[10] = "";

    // Intentar parsear la fecha
    int result = sscanf(date, "%9s %19s %9s", day, month, year);
    if (result != 3)
        return false;

    // Validar día (debe terminar con "st", "nd", "rd", o "th")
    int dayLen = strlen(day);
    if (dayLen < 3)
        return false;

    // Verificar sufijo del día
    char suffix[3];
    strcpy(suffix, &day[dayLen - 2]);

    if (strcmp(suffix, "st") != 0 && strcmp(suffix, "nd") != 0 &&
        strcmp(suffix, "rd") != 0 && strcmp(suffix, "th") != 0) {
        return false;
    }

    // Verificar que la parte numérica del día sean solo dígitos
    for (int i = 0; i < dayLen - 2; i++) {
        if (!isdigit(day[i]))
            return false;
    }

    // Convertir parte numérica del día y validar rango (1-31)
    char dayNum[10] = "";
    strncpy(dayNum, day, dayLen - 2);
    int dayValue = atoi(dayNum);
    if (dayValue < 1 || dayValue > 31)
        return false;

    // Validar mes (meses en inglés)
    const char *months[] = {"January",   "February", "March",    "April",
                            "May",       "June",     "July",     "August",
                            "September", "October",  "November", "December"};

    bool validMonth = false;
    for (int i = 0; i < 12; i++) {
        if (strcasecmp(month, months[i]) == 0) {
            validMonth = true;
            break;
        }
    }
    if (!validMonth)
        return false;

    // Validar año (debe ser numérico y razonable
    int yearLen = strlen(year);
    if (yearLen != 4)
        return false;

    for (int i = 0; i < yearLen; i++) {
        if (!isdigit(year[i]))
            return false;
    }

    int yearValue = atoi(year);
    if (yearValue < 1900 || yearValue > 2025)
        return false;

    return true;
}

// Verificar que la duracion sea valida
bool isValidDuration(const char *length) {
    if (strlen(length) < 3)
        return false;
    // Validación básica: verificar formato con ':'
    int colons = 0;
    for (int i = 0; length[i] != '\0'; i++) {
        if (length[i] == ':')
            colons++;
    }
    return colons >= 1;
}

void insertSongInfo(struct Song *song) {

    bool valid;

    do {
        printf("\nNombre del artista: ");
        fgets(song->artist, ARTIST_MAX, stdin);
        song->artist[strcspn(song->artist, "\n")] = '\0';

        valid = isValidString(song->artist, ARTIST_MAX);

        if (!valid) {
            printf("El nombre no es válido o la entrada supera los 100 bytes");
        }

    } while (!valid);

    do {
        printf("\nNombre de la canción: ");
        fgets(song->name, NAME, stdin);
        song->name[strcspn(song->name, "\n")] = '\0';

        valid = isValidString(song->name, NAME);
        if (!valid) {
            printf("Error: El nombre de la canción no puede estar vacío o la "
                   "entrada supera los 300 bytes.\n");
        }
    } while (!valid);

    do {
        printf("\n Letra de la canción: ");
        fgets(song->text, TEXT, stdin);
        song->text[strcspn(song->text, "\n")] = '\0';

        valid = isValidString(song->text, TEXT);
        if (!valid) {
            printf("Error: La letra no puede estar vacía o la entrada supera "
                   "los 10000 bytes.\n");
        }
    } while (!valid);

    do {
        printf("\nDuración (MM:SS): ");
        fgets(song->length, ARTIST_MAX, stdin);
        song->length[strcspn(song->length, "\n")] = '\0';

        valid = isValidDuration(song->length);
        if (!valid) {
            printf("Error: Formato de duración inválido. Use MM:SS.\n");
        }
    } while (!valid);

    do {
        printf("\nEmoción: ");
        fgets(song->emotion, ARTIST_MAX, stdin);
        song->emotion[strcspn(song->emotion, "\n")] = '\0';

        valid = isValidString(song->emotion, ARTIST_MAX);
        if (!valid) {
            printf("Error: La emoción no puede estar vacía o la entrada supera "
                   "los 100 bytes.\n");
        }
    } while (!valid);

    do {
        printf("\nGénero: ");
        fgets(song->genre, ARTIST_MAX, stdin);
        song->genre[strcspn(song->genre, "\n")] = '\0';

        valid = isValidString(song->genre, ARTIST_MAX);
        if (!valid) {
            printf("Error: El género no puede estar vacío o la entrada supera "
                   "los 100 bytes.\n");
        }
    } while (!valid);

    do {
        printf("\nÁlbum: ");
        fgets(song->album, NAME, stdin);
        song->album[strcspn(song->album, "\n")] = '\0';

        valid = isValidString(song->album, NAME);
        if (!valid) {
            printf("Error: El nombre del álbum no puede estar vacío o la "
                   "entrada supera los 300 bytes.\n");
        }
    } while (!valid);

    do {
        printf("\nFecha (Día ordinal(st, nd, rd, th) Mes Año): ");
        fgets(song->date, NAME, stdin);
        song->date[strcspn(song->date, "\n")] = '\0';

        valid = isValidDate(song->date);
        if (!valid) {
            printf("Error: Formato de fecha inválido. Use (Día ordinal(st, nd, "
                   "rd, th) Mes Año).\n");
        }
    } while (!valid);

    song->nextOffset=-1;
}

int main() {
    int fd, r;
    struct sockaddr_in client;

    struct Comunication comunicacion;

    printf("\nConectando con el motor de busqueda\n");

    fd = socket(AF_INET, SOCK_STREAM, 0);

    if (fd == -1) {
        perror("error al crear el socket");
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip del servidor :D

    memset(&(client.sin_zero), 0, 8);

    r = connect(fd, (struct sockaddr *)&client, sizeof(struct sockaddr_in));
    if (r == -1) {
        perror("error al hacer la conexion");
        exit(1);
    }

    printf("conectado\n");

    // Asignar memoria dinámica para buffers de entrada
    char *artist = (char *)malloc(ARTIST_MAX * sizeof(char));
    char *songName = (char *)malloc(NAME * sizeof(char));

    if (!artist || !songName) {
        perror("Error al asignar memoria");
        return 1;
    }

    int option;

    while (1) {
        printMenu();

        if (scanf("%d", &option) != 1) {
            clearInputBuffer();
            printf("\nOpcion invalida.\n");
            continue;
        }
        clearInputBuffer();

        switch (option) {
        case 1:
            printf("\nBuscando...\n");
            strncpy(comunicacion.artist, artist, ARTIST_MAX - 1);
            comunicacion.artist[ARTIST_MAX - 1] = '\0';
            printf(comunicacion.artist);

            strncpy(comunicacion.songName, songName, NAME - 1);
            comunicacion.songName[NAME - 1] = '\0';

            r = sendAll(fd, &comunicacion, sizeof(comunicacion));
            if (r == -1) {
                perror("Error enviando petición de busqueda");
            }

            // cuando el servidor responda

            r = recvAll(fd, &comunicacion, sizeof(comunicacion));
            if (r == 0) {
                if (comunicacion.found) {
                    printSongInfo(&comunicacion.song);
                } else {
                    printf("\nNA\n");
                }
            } else {
                perror("Error reciviendo datos");
            }
            break;
        case 2:
            // TODO implementar el menu para meter los datos de la canción
            insertSongInfo(&comunicacion.song);

            comunicacion.registrar = true;
            //printf("\n");
            //printf("%d", comunicacion.registrar);
            //Imprime correctamente

            //Imprimiendo para saber si si se esta llenando la estructura xd
            //printf("\n");
            //printf(comunicacion.song.length);

            r = sendAll(fd, &comunicacion, sizeof(comunicacion));
            if (r == -1) {
                perror("Error al ingresar la canción");
                continue;
            }   
            
            r = recvAll(fd, &comunicacion, sizeof(comunicacion));
            //printf("%d",r);
            if (r == 0) {
                if (comunicacion.validRegister) {
                    printf("\n");
                    printf("Ingresada la cación: \n");
                    printSongInfo(&comunicacion.song);
                } else {
                    printf("\nNA\n");
                }
            } else {
                perror("Error recibiendo datos");
            }
            break;
        case 3: {
            int subOption = 0;
            do {
                printSubMenu();

                if (scanf("%d", &subOption) != 1) {
                    clearInputBuffer();
                    printf("\nOpcion invalida.\n");
                    continue;
                }
                clearInputBuffer();

                switch (subOption) {
                case 1:
                    printf("\nNombre del artista: ");
                    fgets(artist, ARTIST_MAX, stdin);
                    artist[strcspn(artist, "\n")] = '\0';
                    break;
                case 2:
                    printf("Nombre de la cancion: ");
                    fgets(songName, NAME, stdin);
                    songName[strcspn(songName, "\n")] = '\0';
                    break;
                case 3:
                    printf("Regresando...\n");
                    break;
                default:
                    printf("\nOpcion invalida.\n");
                }
            } while (subOption != 3);
            break;
        }
        case 4:
            printf("\nCerrando...\n");
            comunicacion.shouldExit = true;
            r = sendAll(fd, &comunicacion, sizeof(comunicacion));
            free(artist);
            free(songName);
            close(fd);
            return 0;

        default:
            printf("\nOpcion invalida.\n");
        }
    }

    return 0;
}

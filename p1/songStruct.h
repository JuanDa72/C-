#include <stdio.h>
#include <stdbool.h>

#define ARTIST_MAX 100
#define NAME 300
#define TEXT 10000



struct Song {

    char artist[ARTIST_MAX];
    char name[NAME];
    char text[TEXT];
    char length[ARTIST_MAX];
    char emotion[ARTIST_MAX];
    char genre[ARTIST_MAX];
    char album[NAME];
    char date[NAME];
    long nextOffset;
};



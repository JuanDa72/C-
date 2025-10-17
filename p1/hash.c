#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Genera hash único para cada artista
unsigned int hash_artista(const char *artista) {
    unsigned int hash = 0;
    while (*artista) {
        hash = hash * 31 + tolower(*artista++);
    }
    return hash % 1000;
}

// Extrae el nombre del artista desde la línea CSV
char* extraer_artista(const char* linea) {
    const char *start = linea;
    const char *ptr = linea;
    int comillas = 0;
    
    while (*ptr && *ptr != '\n') {
        if (*ptr == '"') comillas = !comillas;
        else if (*ptr == ',' && !comillas) break;
        ptr++;
    }
    
    size_t len = ptr - start;
    if (len == 0) return NULL;
    
    char *artista = malloc(len + 1);
    if (!artista) return NULL;
    
    memcpy(artista, start, len);
    artista[len] = '\0';
    return artista;
}

// Compara si el artista coincide (case-insensitive)
int es_artista(const char *artista, const char *buscar) {
    if (!artista || !buscar) return 0;
    
    const char *a = artista;
    const char *b = buscar;
    
    while (*a && *b) {
        if (tolower(*a++) != tolower(*b++)) return 0;
    }
    return *b == '\0';
}

int main() {

    printf("Hash(!!!) = %d\n", hash_artista("!!!"));
    printf("Hash(*NSYNC) = %d\n", hash_artista("*NSYNC"));


}

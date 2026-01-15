#include "file_io.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_BUF 512
#define FIELD_COUNT 6
#define INITIAL_CAPACITY 16

/* Validate integer string */
static int is_number(const char *s) {
    if (!s || *s == '\0') return 0;
    for (; *s; s++) {
        if (!isdigit((unsigned char)*s)) return 0;
    }
    return 1;
}

int load_movies(const char *filename, MovieRecord **movies, int *count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening movie file");
        return -1;
    }

    char line[LINE_BUF];

    /* Validate header */
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        fprintf(stderr, "Empty file\n");
        return -1;
    }

    /* Read and discard header line */
    if (!fgets(line, sizeof(line), fp)) {
         fclose(fp);
         fprintf(stderr, "Empty file\n");
         return -1;
    }

    int capacity = INITIAL_CAPACITY;
    *movies = malloc(sizeof(MovieRecord) * capacity);
    *count = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *fields[FIELD_COUNT];
        int i = 0;

        char *token = strtok(line, ",\n");
        while (token && i < FIELD_COUNT) {
            fields[i++] = token;
            token = strtok(NULL, ",\n");
        }

        if (i != FIELD_COUNT) {
            fprintf(stderr, "Skipping malformed line\n");
            continue;
        }

        if (!is_number(fields[0]) || !is_number(fields[1])) {
            fprintf(stderr, "Skipping invalid numeric data\n");
            continue;
        }

        if (*count >= capacity) {
            capacity *= 2;
            *movies = realloc(*movies, sizeof(MovieRecord) * capacity);
        }

        MovieRecord *m = &(*movies)[(*count)++];
        m->id = atoi(fields[0]);
        m->year = atoi(fields[1]);
        strncpy(m->title, fields[2], MAX_STR);
        strncpy(m->origin, fields[3], MAX_STR);
        strncpy(m->genre, fields[4], MAX_STR);
        strncpy(m->director, fields[5], MAX_STR);
    }

    fclose(fp);
    return *count;
}

int save_movies(const char *filename, const MovieRecord *movies, int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error saving movie file");
        return -1;
    }

    fprintf(fp, "ID,Release Year,Title,Origin,Genre,Director\n");

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%d,%s,%s,%s,%s\n",
                movies[i].id,
                movies[i].year,
                movies[i].title,
                movies[i].origin,
                movies[i].genre,
                movies[i].director);
    }

    fclose(fp);
    return 0;
}

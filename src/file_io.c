#include "file_io.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "movie.h"
#include "movie_list.h"

#define LINE_BUF 512
#define FIELD_COUNT 6

/* Trim leading/trailing whitespace and remove surrounding double quotes if present.
   This modifies the string in-place. */
static void trim_field(char *s) {
    if (!s) return;

    /* trim leading */
    char *start = s;
    while (*start && isspace((unsigned char)*start)) start++;

    if (start != s) memmove(s, start, strlen(start) + 1);

    /* trim trailing */
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }

    /* remove surrounding double quotes "..." if present */
    if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {
        memmove(s, s + 1, len - 2);
        s[len - 2] = '\0';
    }
}

/* Validate integer string (only digits, non-empty) */
static int is_number(const char *s) {
    if (!s || *s == '\0') return 0;
    for (; *s; ++s) {
        if (!isdigit((unsigned char)*s)) return 0;
    }
    return 1;
}

int load_movies(const char *filename, MovieList *list) {
    if (!filename || !list) return -1;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening movie file");
        return -1;
    }

    char line[LINE_BUF];

    /* Read and discard header line (if any). If file is empty, error out. */
    if (!fgets(line, sizeof(line), fp)) {
        fclose(fp);
        fprintf(stderr, "Empty file\n");
        return -1;
    }

    int loaded = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *fields[FIELD_COUNT];
        int i = 0;

        /* strtok modifies the line buffer in-place */
        char *token = strtok(line, ",\n");
        while (token && i < FIELD_COUNT) {
            trim_field(token);
            fields[i++] = token;
            token = strtok(NULL, ",\n");
        }

        if (i != FIELD_COUNT) {
            fprintf(stderr, "Skipping malformed line (expected %d fields, got %d)\n", FIELD_COUNT, i);
            continue;
        }

        if (!is_number(fields[0]) || !is_number(fields[1])) {
            fprintf(stderr, "Skipping invalid numeric data: id='%s' year='%s'\n", fields[0], fields[1]);
            continue;
        }

        int id = atoi(fields[0]);
        int year = atoi(fields[1]);

        Movie *m = movie_create(
            id,
            year,
            fields[2],
            fields[3],
            fields[4],
            fields[5]
        );

        if (!m) {
            fprintf(stderr, "Allocation failed for movie: %s\n", fields[2]);
            continue;
        }

        movie_list_add(list, m);
        ++loaded;
    }

    fclose(fp);
    return loaded;
}

int save_movies(const char *filename, const MovieList *list) {
    if (!filename || !list) return -1;

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error saving movie file");
        return -1;
    }

    /* Header */
    fprintf(fp, "ID,Release Year,Title,Origin,Genre,Director\n");

    size_t n = movie_list_size(list);
    for (size_t i = 0; i < n; ++i) {
        const Movie *m = movie_list_get(list, i);
        if (!m) continue;

        /* Note: fields are written raw; if you need quoting for commas inside fields
           consider adding quoting/escaping here. */
        fprintf(fp, "%d,%d,%s,%s,%s,%s\n",
                movie_get_id(m),
                movie_get_release_year(m),
                movie_get_title(m) ? movie_get_title(m) : "",
                movie_get_origin(m) ? movie_get_origin(m) : "",
                movie_get_genre(m) ? movie_get_genre(m) : "",
                movie_get_director(m) ? movie_get_director(m) : "");
    }

    fclose(fp);
    return 0;
}
